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


class HuffmanEncoder { //Declara la clase HuffmanEncoder.
public:
    HuffmanEncoder(const std::string& input_text); //Constructor Recibe el texto a comprimir
    
    // Métodos principales 
    void buildHuffmanTree(); //Construye el árbol de Huffman.
    void generateCanonicalCodes(); //Convierte los códigos Huffman obtenidos del árbol en códigos canónicos.
    std::string compress(); //Comprime el texto usando los códigos
    
    //Métodos de visualización y reporte 
    void displayFrequencies() const; //Muestra la frecuencia de cada símbolo 
    void displayTree() const; //;  Imprime el árbol de Huffman en la consola
    void displayCodeTables() const; //Muestra la tabla de símbolos junto con sus códigos Huffman y sus longitudes.
    void displayCompressionStats(const std::string& compressed) const; //Imprime estadísticas de compresión 
    void displayCompressedOutput(const std::string& compressed) const; //Muestra el texto ya comprimido

    // Getters
    double getCompressionRatio() const { return compression_ratio; } //Devuelve el ratio de compresión = tamaño original /tamaño comprimido
    double getReductionPercentage() const { return reduction_percentage; } //Devuelve el porcentaje de reducción

private:
    std::string input_text; //Guarda el texto original que se va a comprimir.
    std::unordered_map<char, int> frequencies; //Un mapa hash que guarda la frecuencia de cada carácter.
    std::shared_ptr<HuffmanNode> root; //Un puntero inteligente que apunta a la raíz del árbol de Huffman.
    std::vector<SymbolInfo> symbol_table; //Un vector que guarda una tabla con información de cada símbolo
    std::unordered_map<char, std::string> canonical_code_map; //Un mapa que asocia:carácter → código canónico en binario.

    int original_size_bits; //Tamaño del texto original en bits.
    int compressed_size_bits; //Tamaño del texto comprimido en bits.
    double compression_ratio; //Relación de compresión (Ratio)
    double reduction_percentage; //Porcentaje de reducción del tamaño

    // Métodos auxiliares
    void calculateFrequencies();
    void extractCodeLengths(std::shared_ptr<HuffmanNode> node, int depth,
                           std::unordered_map<char, std::string>& tree_codes,
                           const std::string& code); //Recorre recursivamente el árbol de Huffman para obtener los códigos y longitudes de cada símbolo.
    void displayTreeHelper(std::shared_ptr<HuffmanNode> node, const std::string& prefix, bool is_left) const;//Imprimir el árbol de manera vertical.
    void displayTreeHorizontal(std::shared_ptr<HuffmanNode> node,
                              const std::string& prefix,
                              bool is_right) const; //Muestra el árbol en formato horizontal
    std::string binaryToHex(const std::string& binary) const; //Convierte una cadena binaria en hexadecimal
};

#endif // HUFFMAN_ENCODER_H
