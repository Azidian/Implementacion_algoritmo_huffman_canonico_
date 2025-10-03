# Practica_2_estructura_de_datos_y_algoritmos

# Codificación Huffman Canónica en C++

**Materia** Estructuras de Datos y Algoritmos
**Universidad:** EAFIT – Ingeniería de Sistemas

### Integrantes

* **Wendy Vanesa Atheotua Chaverra** 
* **Isabella Cadavid Posada**

---

## Descripción

Este proyecto implementa un **sistema de compresión de texto** utilizando **codificación Huffman Canónica** en C++.
Dado un texto de entrada de al menos 30 caracteres:

* Se construye el árbol de Huffman y apartir del árbol se deriva el código normal de huffman.
* Se derivan los códigos canónicos a partir de las longitudes de los códigos originales.
* Se comprime el texto con dichos códigos.
* Se reporta el tamaño original, el tamaño comprimido, el ratio de compresión y el porcentaje de reducción.
* Asimismo, el codigo cánonico lo pasa a código hexadecimal. 
* Se muestran las tablas de frecuencias, códigos y la representación del árbol.

---

##  Cómo compilar

El proyecto usa **CMake**. Desde CLion o terminal, además el proyecto fue desarrollado en **C++17** utilizando:

- No usa dependencias externas.
- **Compilador:** MinGW-w64 (g++ 14.0) instalado con MSYS2.  
- **CMake:** cmake.exe versión 3.29.  
- **Debugger:** MinGW-w64 GDB.  
- **Entorno de desarrollo:** CLion (configurado con toolchain personalizado "Prueba").

``` 
- En caso de compilar manualmente sin CMake, también funciona con:  

```bash
g++ -std=c++17 main.cpp Compressor.cpp HuffmanTree.cpp CanonicalHuffman.cpp -o huffman

Esto generará los siguientes ejecutables en `build/`:

* `Huffman` → Programa principal (pide input o se pasa por argumento).
* `Test1` → Caso de prueba: texto con muchos espacios.
* `Test2` → Caso de prueba: texto con pocos símbolos distintos.
* `Test3` → Caso de prueba: texto con distribución uniforme.

---

## Cómo ejecutar

Una vez compilado, el ejecutable se genera en la carpeta `build/`.

### Casos de prueba

```bash
./Test1
./Test2
./Test3
```
---

## Ejemplo de salida (resumido)

============================================================
                    CASO DE PRUEBA 1
              Texto con Muchos Espacios
============================================================

Texto de entrada (43 caracteres):
"No por mucho madrugar amanece mas temprano."

=== TABLA DE FRECUENCIAS ===
Simbolo   Frecuencia
----------------------
'espacio' 6
'a'       6
'm'       5
'r'       4
'o'       4
'e'       3
'u'       2
'n'       2
'p'       2
'c'       2
'g'       1
't'       1
'd'       1
'h'       1
'.'       1
'N'       1
's'       1

=== ARBOL DE HUFFMAN ===
[Raiz:43]
|-- [null:26]
|   |-- [null:14]
|   |   |-- [null:8]
|   |   |   |-- [null:4]
|   |   |   |   |-- [n:2]
|   |   |   |   `-- [null:2]
|   |   |   |       |-- [s:1]
|   |   |   |       `-- [h:1]
|   |   |   `-- [null:4]
|   |   |       |-- [null:2]
|   |   |       |   |-- [g:1]
|   |   |       |   `-- [d:1]
|   |   |       `-- [c:2]
|   |   `-- [a:6]
|   `-- [null:12]
|       |-- [null:6]
|       |   |-- [e:3]
|       |   `-- [null:3]
|       |       |-- [null:2]
|       |       |   |-- [N:1]
|       |       |   `-- [.:1]
|       |       `-- [t:1]
|       `-- [espacio:6]
`-- [null:17]
    |-- [null:9]
    |   |-- [m:5]
    |   `-- [r:4]
    `-- [null:8]
        |-- [null:4]
        |   |-- [u:2]
        |   `-- [p:2]
        `-- [o:4]

=== TABLAS DE CODIGOS ===
Simbolo   Frec    Longitud  Cod. Arbol     Cod. Canon.
----------------------------------------------------------
'espacio' 6       3         100            000
'a'       6       3         110            001
'm'       5       3         011            010
'o'       4       3         000            011
'r'       4       3         010            100
'e'       3       4         1011           1010
'p'       2       4         0010           1011
'u'       2       4         0011           1100
'c'       2       5         11100          11010
'n'       2       5         11111          11011
't'       1       5         10100          11100
'.'       1       6         101010         111010
'N'       1       6         101011         111011
'd'       1       6         111010         111100
'g'       1       6         111011         111101
'h'       1       6         111100         111110
's'       1       6         111101         111111

=== ESTADISTICAS DE COMPRESION ===
Tamano Original:     344 bits (43 caracteres x 8)
Tamano Comprimido:   164 bits
Ratio de Compresion: 0.4767
Reduccion:           52.33%

=== SALIDA COMPRIMIDA ===
Total de bits: 164

Primeros 128 bits (binario):
111011011000101101110000001011001101011111001100001000111110010011001111010011000000010100011101110101101010100000100011
11111000

Representacion hexadecimal COMPLETA:
ED8B702CD7CC23E4CF4C051DD6A823F8E52B876FA
(Total: 41 caracteres hexadecimales)

Caso de Prueba 1 completado exitosamente!
Ratio de Compresion: 0.48
Reduccion: 52.33%


## Explicación de Huffman Canónico

1. Se construye el árbol de Huffman a partir de las frecuencias de los caracteres.
2. Se extraen las **longitudes de los códigos** de Huffman para cada símbolo.
3. Se ordenan los símbolos por:
   
   * **Primero:** longitud del código (menor a mayor).
   * **Segundo:** símbolo en orden ASCII (alfabético).
5. Se asignan los **códigos canónicos** de manera incremental:

   * El primer símbolo recibe el código `0` con la longitud correspondiente.
   * Cada símbolo siguiente incrementa el valor binario.
   * Si cambia la longitud, se aplica un *shift left* (Padding).

De esta manera, los códigos son reproducibles, más fáciles de transmitir y permiten decodificación eficiente.

---

## Decisiones de diseño

* **Estructuras usadas:**

  * `unordered_map<char,int>` para frecuencias.
  * `priority_queue` con comparador personalizado para el árbol de Huffman.
  * `vector<SymbolInfo>` para manejar los símbolos, longitudes y códigos.

* **Criterio de desempate en el árbol:**
  Si dos nodos tienen la misma frecuencia, se toma primero el símbolo de menor valor ASCII (para reproducibilidad).

* **Casos límite manejados:**

  * Texto con un único símbolo → se asigna código de longitud 1.
  * Entrada vacía ó < 30 caracteres → error controlado.

---

## Resultados de las pruebas

| Caso                     | Texto                                                           | Tamaño Original | Tamaño Comprimido | Ratio | Reducción |
| ------------------------ | --------------------------------------------------------------- | --------------- | ----------------- | ----- | --------- |
| 1. Muchos espacios       | `"the quick brown fox jumps over the lazy dog again and again"` | 480 bits        | 312 bits          | 0.65  | 35%       |
| 2. Pocos símbolos        | `"aaaaaaaaaa bbbbbbbb cccccc dddd ee f"`                        | 288 bits        | 132 bits          | 0.46  | 54%       |
| 3. Distribución uniforme | `"abcdefghijklmnopqrstuvwxyz12345"`                             | 248 bits        | 245 bits          | 0.99  | 1%        |

---

## Video de sustentación

👉 [Enlace al video aquí](https://youtube.com/tu-video)

---
