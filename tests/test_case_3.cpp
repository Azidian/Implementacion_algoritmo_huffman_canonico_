#include <iostream>
#include <string>
#include "../include/huffman_encoder.h"

int main() {
    std::cout << "============================================================\n";
    std::cout << "                    CASO DE PRUEBA 3                        \n";
    std::cout << "          Texto con Distribucion Uniforme                   \n";
    std::cout << "============================================================\n";

    std::string test_text = "abcdefghijklmnopqrstuvwxyz12345";

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

        std::cout << "\n[OK] Caso de Prueba 3 completado exitosamente!\n";
        std::cout << "Ratio de Compresion: " << encoder.getCompressionRatio() << "\n";
        std::cout << "Reduccion: " << encoder.getReductionPercentage() << "%\n";

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "\n[ERROR] " << e.what() << "\n";
        return 1;
    }
}
