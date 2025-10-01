#include "../include/huffman_encoder.h"
#include "../include/huffman_node.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <bitset>
#include <sstream>

HuffmanEncoder::HuffmanEncoder(const std::string& input_text)
    : input_text(input_text), root(nullptr), original_size_bits(0),
      compressed_size_bits(0), compression_ratio(0.0), reduction_percentage(0.0) {

    if (input_text.length() < 30) {
        throw std::invalid_argument("El texto de entrada debe tener al menos 30 caracteres");
    }

    calculateFrequencies();
    original_size_bits = input_text.length() * 8;
}

void HuffmanEncoder::calculateFrequencies() {
    for (char c : input_text) {
        frequencies[c]++;
    }
}

void HuffmanEncoder::buildHuffmanTree() {
    std::priority_queue<std::shared_ptr<HuffmanNode>,
                       std::vector<std::shared_ptr<HuffmanNode>>,
                       NodeComparator> pq;

    for (const auto& pair : frequencies) {
        pq.push(std::make_shared<HuffmanNode>(pair.first, pair.second));
    }

    if (pq.size() == 1) {
        auto single_node = pq.top();
        pq.pop();
        root = std::make_shared<HuffmanNode>(single_node->frequency, single_node, nullptr);
        return;
    }

    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();

        int combined_freq = left->frequency + right->frequency;
        auto parent = std::make_shared<HuffmanNode>(combined_freq, left, right);
        pq.push(parent);
    }

    root = pq.top();
}

void HuffmanEncoder::extractCodeLengths(std::shared_ptr<HuffmanNode> node, int depth,
                                       std::unordered_map<char, std::string>& tree_codes,
                                       const std::string& code) {
    if (!node) return;

    if (node->is_leaf) {
        tree_codes[node->symbol] = code.empty() ? "0" : code;
        symbol_table.push_back(SymbolInfo(node->symbol, node->frequency,
                                         code.empty() ? 1 : depth, tree_codes[node->symbol]));
        return;
    }

    extractCodeLengths(node->left, depth + 1, tree_codes, code + "0");
    extractCodeLengths(node->right, depth + 1, tree_codes, code + "1");
}

void HuffmanEncoder::generateCanonicalCodes() {
    std::unordered_map<char, std::string> tree_codes;
    extractCodeLengths(root, 0, tree_codes, "");

    std::sort(symbol_table.begin(), symbol_table.end(),
              [](const SymbolInfo& a, const SymbolInfo& b) {
                  if (a.code_length != b.code_length) {
                      return a.code_length < b.code_length;
                  }
                  return a.symbol < b.symbol;
              });

    int code_value = 0;
    int prev_length = 0;

    for (auto& info : symbol_table) {
        if (info.code_length > prev_length && prev_length > 0) {
            code_value <<= (info.code_length - prev_length);
        }

        std::string canonical = "";
        for (int i = info.code_length - 1; i >= 0; i--) {
            canonical += ((code_value >> i) & 1) ? '1' : '0';
        }

        info.canonical_code = canonical;
        canonical_code_map[info.symbol] = canonical;

        code_value++;
        prev_length = info.code_length;
    }
}

std::string HuffmanEncoder::compress() {
    std::string compressed = "";
    for (char c : input_text) {
        compressed += canonical_code_map[c];
    }

    compressed_size_bits = compressed.length();
    compression_ratio = static_cast<double>(compressed_size_bits) / original_size_bits;
    reduction_percentage = (1.0 - compression_ratio) * 100.0;

    return compressed;
}

void HuffmanEncoder::displayFrequencies() const {
    std::cout << "\n=== TABLA DE FRECUENCIAS ===\n";
    std::cout << std::left << std::setw(10) << "Simbolo"
              << std::setw(12) << "Frecuencia" << "\n";
    std::cout << std::string(22, '-') << "\n";

    std::vector<std::pair<char, int>> sorted_freq(frequencies.begin(), frequencies.end());
    std::sort(sorted_freq.begin(), sorted_freq.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    for (const auto& pair : sorted_freq) {
        std::string symbol_display = (pair.first == ' ') ? "'espacio'" :
                                    (pair.first == '\n') ? "'\\n'" :
                                    "'" + std::string(1, pair.first) + "'";
        std::cout << std::left << std::setw(10) << symbol_display
                  << std::setw(12) << pair.second << "\n";
    }
}

void HuffmanEncoder::displayTreeHorizontal(std::shared_ptr<HuffmanNode> node,
                                          const std::string& prefix,
                                          bool is_right) const {
    if (!node) return;

    std::cout << prefix;
    std::cout << (is_right ? "|-- " : "`-- ");

    if (node->is_leaf) {
        std::string symbol_display = (node->symbol == ' ') ? "espacio" :
                                    (node->symbol == '\n') ? "\\n" :
                                    std::string(1, node->symbol);
        std::cout << "[" << symbol_display << ":" << node->frequency << "]\n";
    } else {
        std::cout << "[null:" << node->frequency << "]\n";
    }

    if (node->right) {
        displayTreeHorizontal(node->right, prefix + (is_right ? "|   " : "    "), true);
    }
    if (node->left) {
        displayTreeHorizontal(node->left, prefix + (is_right ? "|   " : "    "), false);
    }
}

void HuffmanEncoder::displayTree() const {
    std::cout << "\n=== ARBOL DE HUFFMAN ===\n";
    if (root) {
        std::cout << "[Raiz:" << root->frequency << "]\n";
        if (root->right) {
            displayTreeHorizontal(root->right, "", true);
        }
        if (root->left) {
            displayTreeHorizontal(root->left, "", false);
        }
    }
}

void HuffmanEncoder::displayCodeTables() const {
    std::cout << "\n=== TABLAS DE CODIGOS ===\n";
    std::cout << std::left
              << std::setw(10) << "Simbolo"
              << std::setw(8) << "Frec"
              << std::setw(10) << "Longitud"
              << std::setw(15) << "Cod. Arbol"
              << std::setw(15) << "Cod. Canon." << "\n";
    std::cout << std::string(58, '-') << "\n";

    for (const auto& info : symbol_table) {
        std::string symbol_display = (info.symbol == ' ') ? "'espacio'" :
                                    (info.symbol == '\n') ? "'\\n'" :
                                    "'" + std::string(1, info.symbol) + "'";
        std::cout << std::left
                  << std::setw(10) << symbol_display
                  << std::setw(8) << info.frequency
                  << std::setw(10) << info.code_length
                  << std::setw(15) << info.tree_code
                  << std::setw(15) << info.canonical_code << "\n";
    }
}

void HuffmanEncoder::displayCompressionStats(const std::string& compressed) const {
    std::cout << "\n=== ESTADISTICAS DE COMPRESION ===\n";
    std::cout << "Tamano Original:     " << original_size_bits << " bits ("
              << input_text.length() << " caracteres x 8)\n";
    std::cout << "Tamano Comprimido:   " << compressed_size_bits << " bits\n";
    std::cout << "Ratio de Compresion: " << std::fixed << std::setprecision(4)
              << compression_ratio << "\n";
    std::cout << "Reduccion:           " << std::fixed << std::setprecision(2)
              << reduction_percentage << "%\n";
}

std::string HuffmanEncoder::binaryToHex(const std::string& binary) const {
    std::string hex = "";
    std::string padded = binary;

    while (padded.length() % 4 != 0) {
        padded += "0";
    }

    for (size_t i = 0; i < padded.length(); i += 4) {
        std::string nibble = padded.substr(i, 4);
        int value = std::stoi(nibble, nullptr, 2);
        hex += "0123456789ABCDEF"[value];
    }

    return hex;
}

void HuffmanEncoder::displayCompressedOutput(const std::string& compressed) const {
    std::cout << "\n=== SALIDA COMPRIMIDA ===\n";
    std::cout << "Total de bits: " << compressed.length() << "\n";

    std::cout << "\nPrimeros " << std::min(128, (int)compressed.length()) << " bits (binario):\n";
    std::cout << compressed.substr(0, std::min(128, (int)compressed.length())) << "\n";

    std::cout << "\nRepresentacion hexadecimal COMPLETA:\n";
    std::string hex_complete = binaryToHex(compressed);
    std::cout << hex_complete << "\n";
    std::cout << "(Total: " << hex_complete.length() << " caracteres hexadecimales)\n";
}
