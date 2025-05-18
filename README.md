# Symmetric NMF Clustering

an implementation of Symmetric Non-negative Matrix Factorization (SymNMF) for graph-based clustering, a comparison to K-means, and tools to build and run both the C and Python interfaces.

---

- **symnmf.c**           — C implementation of similarity, degree, normalization, and NMF updates
- **symnmf.h**           — Header file for symnmf.c
- **symnmfmodule.c**     — Python-C API wrapper exposing symnmf routines
- **symnmf.py**          — High-level Python interface
- **kmeans.py**          — Python K-means for comparison
- **analysis.py**        — Driver script: runs SymNMF vs. K-means & prints silhouette scores
- **setup.py**           — setuptools script to build the Python extension in-place
- **Makefile**           — rules to compile the symnmf C executable
- **README.md**          

---

# build & run

1. **Input Format**  
   - The program reads a `.txt` file containing N data points in ℝᵈ, one point per line (coordinates separated by commas or whitespace).

2. **C Executable**  
   - **Using make**  
     - `make`  
     - `./symnmf <goal> <input_file>`  
   - **Without make**  
     - `gcc -fPIC -shared -o symnmf symnmf.c symnmfmodule.c $(python3-config --cflags --ldflags)`  
     - `./symnmf <goal> <input_file>`

3. **Python Interface**  
   - **Build the extension**  
     - `python3 setup.py build_ext --inplace`  
   - **Run**  
     - `python3 symnmf.py <k> <goal> <input_file>`

4. **Output Format**  
   - Writes a matrix to stdout:  
     - One row per line  
     - Entries separated by commas  
     - Values formatted to 4 decimal places (e.g. `0.1234`)

