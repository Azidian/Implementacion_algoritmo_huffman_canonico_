//Evitan que este archivo se incluya más de una vez en la compilación.
//Si el compilador ya ha visto este archivo, no lo volverá a procesar.
//Y si no ha visto un archivo de este, lo define y procesa el contenido.

#ifndef HUFFMAN_ENCODER_H 
#define HUFFMAN_ENCODER_H

#include <string> //Para manejo de cadenas
#include <unordered_map> //Para tablas hash 
#include <vector> //Para almacenar la tabla de símbolos
#include <memory> //Contiene utilidades para manejo de memoria dinámica
#include "huffman_node.h" //Archivo propio con la definición del nodo del árbol

//Almacena información completa de cada símbolo
struct SymbolInfo {
    char symbol; //El carácter original
    int frequency; //Cuántas veces aparece
    int code_length; //Longitud del código Huffman
    std::string tree_code;      //Código de huffman directamente obtenido del árbol 
    std::string canonical_code; //Código transformado a canónico 

    //Inicializa todos los miembros, dejando canonical_code vacío
    SymbolInfo(char sym, int freq, int len, const std::string& tree_c)
        : symbol(sym), frequency(freq), code_length(len), tree_code(tree_c), canonical_code("") {}
};


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
