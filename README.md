# CSCI311--SortingAlgorithms
Sorting Algorithms performance taking random values and sizes into consideration.

# **Sorting Algorithm Performance Analysis**

This project implements and evaluates the performance of various sorting algorithms using datasets of varying sizes. The algorithms are tested under three scenarios: best-case (sorted), worst-case (reversed), and average-case (randomized). Results are written to a CSV file and visualized using Python's Matplotlib library.

---

## **Algorithms Implemented**
1. **Bubble Sort**
2. **Insertion Sort**
3. **Selection Sort**
4. **Merge Sort**
5. **Quick Sort** (with different pivot strategies):
   - Random Pivot
   - Min Pivot
   - Max Pivot
   - Median of Medians Pivot

---

## **Features**
- **Benchmarking**: Measures sorting times for:
  - **Best Case**: Pre-sorted arrays
  - **Worst Case**: Reverse-sorted arrays
  - **Average Case**: Randomized arrays (average of 30 runs)
- **Results Output**:
  - Saves results to a CSV file: `sorting_results.csv`
- **Graph Visualization**:
  - Generates comparison graphs of sorting algorithm performances in `sorting_results.png`.

---

## **Getting Started**

### **Prerequisites**
1. **C++ Compiler**: Ensure `g++` is installed.
2. **Python**: Version 3.6 or higher is required.
3. **Python Matplotlib Library**: Install it by running:
   ```bash
   pip install matplotlib
4.Matplotlib.cpp/Excel
