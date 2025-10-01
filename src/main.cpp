#include <iostream>
#include <string>
#include "../include/huffman_encoder.h"

void printHeader() {
    std::cout << "============================================================\n";
    std::cout << "               CODIFICACION HUFFMAN CANONICA                \n";
    std::cout << "             Estructuras de Datos y Algoritmos                \n";
    std::cout << "============================================================\n";
}

int main(int argc, char* argv[]) {
    printHeader();

    std::string input_text;

    if (argc > 1) {
        input_text = argv[1];
    } else {
        std::cout << "\nIngrese el texto a comprimir (minimo 30 caracteres):\n";
        std::getline(std::cin, input_text);
    }

    try {
        // Crear encoder
        HuffmanEncoder encoder(input_text);

        std::cout << "\nTexto de entrada (" << input_text.length() << " caracteres):\n";
        std::cout << "\"" << input_text << "\"\n";

        // Paso 1: Construir arbol de Huffman
        std::cout << "\n[Paso 1] Construyendo arbol de Huffman...\n";
        encoder.buildHuffmanTree();
        encoder.displayFrequencies();
        encoder.displayTree();

        // Paso 2: Generar codigos canonicos
        std::cout << "\n[Paso 2] Generando codigos canonicos...\n";
        encoder.generateCanonicalCodes();
        encoder.displayCodeTables();

        // Paso 3: Comprimir
        std::cout << "\n[Paso 3] Comprimiendo texto...\n";
        std::string compressed = encoder.compress();
        encoder.displayCompressionStats(compressed);
        encoder.displayCompressedOutput(compressed);

        std::cout << "\n[OK] Compresion completada exitosamente!\n";

    } catch (const std::exception& e) {
        std::cerr << "\n[ERROR] " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
