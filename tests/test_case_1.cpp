#include <iostream>
#include <string>
#include "../include/huffman_encoder.h"

int main() {
    std::cout << "============================================================\n";
    std::cout << "                    CASO DE PRUEBA 1                        \n";
    std::cout << "              Texto con Muchos Espacios                     \n";
    std::cout << "============================================================\n";

    std::string test_text = "No por mucho madrugar amanece mas temprano.";

    try {
        HuffmanEncoder encoder(test_text);

        std::cout << "\nTexto de entrada (" << test_text.length() << " caracteres):\n";
        std::cout << "\"" << test_text << "\"\n";

        encoder.buildHuffmanTree();
        encoder.displayFrequencies();
        encoder.displayTree();

        encoder.generateCanonicalCodes();
        encoder.displayCodeTables();

        std::string compressed = encoder.compress();
        encoder.displayCompressionStats(compressed);
        encoder.displayCompressedOutput(compressed);

        std::cout << "\n[OK] Caso de Prueba 1 completado exitosamente!\n";
        std::cout << "Ratio de Compresion: " << encoder.getCompressionRatio() << "\n";
        std::cout << "Reduccion: " << encoder.getReductionPercentage() << "%\n";

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "\n[ERROR] " << e.what() << "\n";
        return 1;
    }
}
