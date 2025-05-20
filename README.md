# Symmetric NMF Clustering

Implementation of Symmetric Non-negative Matrix Factorization (SymNMF) for graph-based clustering, a comparison to K-means, and tools to build and run both the C and Python interfaces.

---

- **symnmf.c**           — C implementation of similarity, degree, normalization, and NMF updates
- **symnmf.h**           — Header file for symnmf.c
- **symnmfmodule.c**     — Python-C API wrapper exposing symnmf routines
- **symnmf.py**          — High-level Python interface
- **kmeans.py**          — Python K-means for comparison
- **analysis.py**        — Driver script: runs SymNMF vs. K-means & prints silhouette scores
- **setup.py**           — setuptools script to build the Python extension in-place
- **Makefile**           — rules to compile the symnmf C executable         

---

## Build & Run

1. **C Executable**
   - Build: `make`
   - Run: `./symnmf <goal> <input_file>`
     - `<goal>` ∈ {sym, ddg, norm}
       - sym  — compute similarity matrix A
       - ddg  — compute degree matrix D
       - norm — compute normalized similarity W = D⁻¹ᐟ² A D⁻¹ᐟ²
     - `<input_file>` — path to your `.txt` data file containing N data points in ℝᵈ, one point per line (coordinates separated by commas or whitespace)

2. **Python Interface**
   - Build extension: `python3 setup.py build_ext --inplace`
   - Run: `python3 symnmf.py <k> <goal> <input_file>`
     - `<k>` — number of clusters
     - `<goal>` ∈ {sym, ddg, norm, symnmf}
       - symnmf — runs full factorization and outputs H ∈ ℝ^{N×k}
     - `<input_file>` — path to your `.txt` data file

3. **Analysis Script**  
   - Run: `python3 analysis.py <k> <input_file>`
   - Prints:
     ```
     nmf:    <silhouette_score>
     kmeans: <silhouette_score>
     ```  
   - Silhouette score ∈ [–1, 1]

---

## Output Format & Interpretation

All routines write to **stdout** as a comma-separated matrix, rows on separate lines:

- **sym**   → similarity matrix A
- **ddg**   → degree matrix D
- **norm**  → normalized similarity W = D⁻¹ᐟ² A D⁻¹ᐟ²
- **symnmf**→ factor H, each row’s max entry indicates cluster assignment
- **analysis.py**→ silhouette scores for SymNMF vs. K-means
