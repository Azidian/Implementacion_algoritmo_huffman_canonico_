#ifndef HUFFMAN_ENCODER_H
#define HUFFMAN_ENCODER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "huffman_node.h"

/**
 * Structure to hold symbol information for canonical code generation
 */
struct SymbolInfo {
    char symbol;
    int frequency;
    int code_length;
    std::string tree_code;      // Non-canonical code from tree
    std::string canonical_code; // Canonical code

    SymbolInfo(char sym, int freq, int len, const std::string& tree_c)
        : symbol(sym), frequency(freq), code_length(len), tree_code(tree_c), canonical_code("") {}
};

/**
 * Main Huffman encoder class implementing canonical Huffman coding
 */
class HuffmanEncoder {
public:
    HuffmanEncoder(const std::string& input_text);
    
    // Main operations
    void buildHuffmanTree();
    void generateCanonicalCodes();
    std::string compress();
    
    // Visualization and reporting
    void displayFrequencies() const;
    void displayTree() const;
    void displayCodeTables() const;
    void displayCompressionStats(const std::string& compressed) const;
    void displayCompressedOutput(const std::string& compressed) const;

    // Getters
    double getCompressionRatio() const { return compression_ratio; }
    double getReductionPercentage() const { return reduction_percentage; }

private:
    std::string input_text;
    std::unordered_map<char, int> frequencies;
    std::shared_ptr<HuffmanNode> root;
    std::vector<SymbolInfo> symbol_table;
    std::unordered_map<char, std::string> canonical_code_map;

    int original_size_bits;
    int compressed_size_bits;
    double compression_ratio;
    double reduction_percentage;

    // Helper methods
    void calculateFrequencies();
    void extractCodeLengths(std::shared_ptr<HuffmanNode> node, int depth,
                           std::unordered_map<char, std::string>& tree_codes,
                           const std::string& code);
    void displayTreeHelper(std::shared_ptr<HuffmanNode> node, const std::string& prefix, bool is_left) const;
    void displayTreeHorizontal(std::shared_ptr<HuffmanNode> node,
                              const std::string& prefix,
                              bool is_right) const;
    std::string binaryToHex(const std::string& binary) const;
};

#endif // HUFFMAN_ENCODER_H
