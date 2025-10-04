# Practica_2_estructura_de_datos_y_algoritmos

# Codificación Huffman Canónica en C++

**Materia** Estructuras de Datos y Algoritmos
**Universidad:** EAFIT – Ingeniería de Sistemas

### Integrantes

* **Wendy Vanesa Atehortua Chaverra** 
* **Isabella Cadavid Posada**

---

## Descripción

Este proyecto implementa un **sistema de compresión de texto** utilizando la **codificación Huffman Canónica** en C++.
Dado un texto de entrada de al menos 30 caracteres:

* Se construye el árbol de Huffman y apartir del árbol se deriva el código normal de huffman.
* Se derivan los códigos canónicos a partir de las longitudes de los códigos originales.
* Se comprime el texto con dichos códigos.
* Se reporta el tamaño original, el tamaño comprimido, el ratio de compresión teorico y el porcentaje de reducción. (Tenga en cuenta que se usan 8 bits al almacenar, es decir, si su texto comprimido usa 73 bits de manera teorica, en realidad está usando 80 bits en vez de 9 bytes y un bit.)
* Asimismo, el codigo cánonico lo pasa a código hexadecimal. 
* Se muestran las tablas de frecuencias, códigos y la representación del árbol por consola. 

---
## Estructura del proyecto

include/ # Archivos de cabecera (.h)
src/ # Código fuente principal (.cpp)
main.cpp # Punto de entrada del programa (ejecutable huffman)

tests/ # Casos de prueba (ejecutable tests)
- Test_1.cpp 
- Test_2.cpp 
- Test_3.cpp 

CMakeLists.txt # Configuración de CMake
gitignore

---

##  Cómo compilar

### Usando CLion
1. Abrir el proyecto en CLion.  
2. CLion detectará automáticamente `CMakeLists.txt`.  
3. Seleccionar la configuración de ejecución (arriba a la derecha):  
   - `huffman` → ejecuta el programa principal.  
   - `tests` → ejecuta los casos de prueba. (Elegir el caso de prueba a ejecutar) 
4. Presionar  **Run**.  


### Usando terminal (Linux/Mac/MinGW)
Desde la raíz del proyecto:

```bash
# Crear carpeta de compilación
mkdir build
cd build

# Generar archivos de compilación
cmake ..

# Compilar
cmake --build .

# Ejecutar el programa principal
./huffman

# Ejecutar los tests
./tests
```
### También puede usarse
.\huffman.exe
.\tests.exe

### Compilación manual sin CMake

```bash
g++ -std=c++17 main.cpp Compressor.cpp HuffmanTree.cpp CanonicalHuffman.cpp -o huffman

Esto generará los siguientes ejecutables en `build/`:

* `Huffman` → Programa principal (pide input o se pasa por argumento).
* `Test1` → Caso de prueba: texto con muchos espacios.
* `Test2` → Caso de prueba: texto con pocos símbolos distintos.
* `Test3` → Caso de prueba: texto con distribución uniforme.

```

## Cómo ejecutar

Una vez compilado, el ejecutable se genera en la carpeta `build/`.

El proyecto usa **CMake**. Desde CLion o terminal, además el proyecto fue desarrollado en **C++17** utilizando:
- No usa dependencias externas.
- **Compilador:** MinGW-w64 (g++ 14.0) instalado con MSYS2.  
- **CMake:** cmake.exe versión 3.29.  
- **Debugger:** MinGW-w64 GDB.  
- **Entorno de desarrollo:** CLion (configurado con toolchain personalizado "Prueba").

---

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

👉 [Enlace al video aquí]([https://youtube.com/tu-video](https://youtu.be/KRgI169TccQ?si=NQKAIc4WEVWg8IPL))

---
