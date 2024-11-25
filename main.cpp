#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;
using namespace std::chrono;

// Function to generate random data
vector<int> generateRandomVector(int size, int lower = 0, int upper = 10000) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(lower, upper);

    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// Function to generate sorted data (best case)
vector<int> generateSortedVector(int size) {
    vector<int> arr = generateRandomVector(size);
    sort(arr.begin(), arr.end());
    return arr;
}

// Function to generate reversed data (worst case)
vector<int> generateReversedVector(int size) {
    vector<int> arr = generateSortedVector(size);
    reverse(arr.begin(), arr.end());
    return arr;
}

// Measure sorting time
template <typename SortFunction>
double measureSortingTime(SortFunction sortFunc, vector<int> arr) {
    auto start = high_resolution_clock::now();
    sortFunc(arr); // Sort the copy
    auto end = high_resolution_clock::now();
    return duration_cast<duration<double>>(end - start).count();
}

// Compute average time for shuffling and sorting (average case)
double computeAverageTime(vector<int> arr, void (*sortFunc)(vector<int>&), int permutations = 30) {
    random_device rd;
    mt19937 gen(rd());
    double totalTime = 0.0;

    for (int i = 0; i < permutations; i++) {
        shuffle(arr.begin(), arr.end(), gen); // Shuffle the array
        auto start = high_resolution_clock::now();
        sortFunc(arr); // Sort the shuffled array
        auto end = high_resolution_clock::now();
        totalTime += duration_cast<duration<double>>(end - start).count();
    }

    return totalTime / permutations; // Return the average time
}

// Bubble Sort implementation
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    int i = n;
    while (i > 0) {
        bool isSwap = false;
        for (int j = 0; j < i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                isSwap = true;
                swap(arr[j], arr[j + 1]);
            }
        }
        if (!isSwap) break;
        i--;
    }
}

// Insertion Sort implementation
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Selection Sort implementation
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Merge Sort implementation
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Wrapper for Merge Sort
void mergeSortWrapper(vector<int>& arr) {
    mergeSort(arr, 0, arr.size() - 1);
}

//Quick sort Algorithms taking pivot as random, maximum, minimum, median of medians of 5

int partitionRandomPivot(vector<int>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortRandomPivot(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionRandomPivot(arr, low, high);
        quickSortRandomPivot(arr, low, pi - 1);
        quickSortRandomPivot(arr, pi + 1, high);
    }
}

void quickSortRandomPivotWrapper(vector<int>& arr) {
    quickSortRandomPivot(arr, 0, arr.size() - 1);
}

int partitionMinPivot(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low + 1, j = high;
    while (true) {
        while (i <= j && arr[i] <= pivot) i++;
        while (i <= j && arr[j] > pivot) j--;
        if (i > j) break;
        swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}

void quickSortMinPivot(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionMinPivot(arr, low, high);
        quickSortMinPivot(arr, low, pi - 1);
        quickSortMinPivot(arr, pi + 1, high);
    }
}

void quickSortMinPivotWrapper(vector<int>& arr) {
    quickSortMinPivot(arr, 0, arr.size() - 1);
}

int partitionMaxPivot(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortMaxPivot(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionMaxPivot(arr, low, high);
        quickSortMaxPivot(arr, low, pi - 1);
        quickSortMaxPivot(arr, pi + 1, high);
    }
}

void quickSortMaxPivotWrapper(vector<int>& arr) {
    quickSortMaxPivot(arr, 0, arr.size() - 1);
}

// Median of Medians QuickSort
int medianOfFive(vector<int>& arr, int start) {
    sort(arr.begin() + start, arr.begin() + start + 5);
    return arr[start + 2];
}

int medianOfMedians(vector<int>& arr, int low, int high) {
    int n = high - low + 1;
    vector<int> medians;
    for (int i = low; i <= high; i += 5) {
        if (i + 4 <= high) {
            medians.push_back(medianOfFive(arr, i));
        } else {
            sort(arr.begin() + i, arr.begin() + high + 1);
            medians.push_back(arr[i + (high - i) / 2]);
        }
    }
    if (medians.size() == 1) return medians[0];
    return medianOfMedians(medians, 0, medians.size() - 1);
}

int partitionMedianOfMedians(vector<int>& arr, int low, int high) {
    int pivot = medianOfMedians(arr, low, high);
    int i = low, j = high;

    while (true) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i >= j) return j;
        swap(arr[i], arr[j]);
        i++;
        j--;
    }
}

void quickSortMedianOfMedians(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionMedianOfMedians(arr, low, high);
        quickSortMedianOfMedians(arr, low, pi);
        quickSortMedianOfMedians(arr, pi + 1, high);
    }
}

void quickSortMedianOfMediansWrapper(vector<int>& arr) {
    quickSortMedianOfMedians(arr, 0, arr.size() - 1);
}
// Function to write results to CSV
// Function to write results to CSV
void writeResultsToCSV(const string& filename, vector<int>& sizes,
                       const vector<vector<double>>& bubbleTimes,
                       const vector<vector<double>>& insertionTimes,
                       const vector<vector<double>>& selectionTimes,
                       const vector<vector<double>>& mergeTimes,
                       const vector<vector<double>>& randomTimes,
                       const vector<vector<double>>& minTimes,
                       const vector<vector<double>>& maxTimes,
                       const vector<vector<double>>& medianTimes
                       ) {
    ofstream outFile(filename);
    outFile << "Size,Algorithm,Case,Time (seconds)\n";

    for (size_t i = 0; i < sizes.size(); ++i) {
        int size = sizes[i];
        outFile << size << ",Bubble Sort,Sorted," << bubbleTimes[i][0] << "\n";
        outFile << size << ",Bubble Sort,Reversed," << bubbleTimes[i][1] << "\n";
        outFile << size << ",Bubble Sort,Average," << bubbleTimes[i][2] << "\n";

        outFile << size << ",Insertion Sort,Sorted," << insertionTimes[i][0] << "\n";
        outFile << size << ",Insertion Sort,Reversed," << insertionTimes[i][1] << "\n";
        outFile << size << ",Insertion Sort,Average," << insertionTimes[i][2] << "\n";

        outFile << size << ",Selection Sort,Sorted," << selectionTimes[i][0] << "\n";
        outFile << size << ",Selection Sort,Reversed," << selectionTimes[i][1] << "\n";
        outFile << size << ",Selection Sort,Average," << selectionTimes[i][2] << "\n";

        outFile << size << ",Merge Sort,Sorted," << mergeTimes[i][0] << "\n";
        outFile << size << ",Merge Sort,Reversed," << mergeTimes[i][1] << "\n";
        outFile << size << ",Merge Sort,Average," << mergeTimes[i][2] << "\n";

        outFile << size << ",QuickSort-Random,Sorted," << randomTimes[i][0] << "\n";
        outFile << size << ",QuickSort-Random,Reversed," << randomTimes[i][1] << "\n";
        outFile << size << ",QuickSort-Random,Average," << randomTimes[i][2] << "\n";

        outFile << size << ",QuickSort-Min,Sorted," << minTimes[i][0] << "\n";
        outFile << size << ",QuickSort-Min,Reversed," << minTimes[i][1] << "\n";
        outFile << size << ",QuickSort-Min,Average," << minTimes[i][2] << "\n";

        outFile << size << ",QuickSort-Max,Sorted," << maxTimes[i][0] << "\n";
        outFile << size << ",QuickSort-Max,Reversed," << maxTimes[i][1] << "\n";
        outFile << size << ",QuickSort-Max,Average," << maxTimes[i][2] << "\n";

        outFile << size << ",QuickSort-Median,Sorted," << medianTimes[i][0] << "\n";
        outFile << size << ",QuickSort-Median,Reversed," << medianTimes[i][1] << "\n";
        outFile << size << ",QuickSort-Median,Average," << medianTimes[i][2] << "\n";
    }

    outFile.close();
}



int main() {
    srand(time(0)); // Seed for random pivot
    vector<int> sizes = {10, 100, 1000, 10000};

    // Data structure to store times
    vector<vector<double>> bubbleTimes(sizes.size(), vector<double>(3, 0.0));
    vector<vector<double>> insertionTimes(sizes.size(), vector<double>(3, 0.0));
    vector<vector<double>> selectionTimes(sizes.size(), vector<double>(3, 0.0));
    vector<vector<double>> mergeTimes(sizes.size(), vector<double>(3, 0.0));
    vector<vector<double>> quickRandomTimes(sizes.size(), vector<double>(3, 0.0));
    vector<vector<double>> quickMinTimes(sizes.size(), vector<double>(3, 0.0));
    vector<vector<double>> quickMaxTimes(sizes.size(), vector<double>(3, 0.0));
    vector<vector<double>> quickMedianTimes(sizes.size(), vector<double>(3, 0.0));

    for (size_t i = 0; i < sizes.size(); ++i) {
        int size = sizes[i];

        // Generate data
        vector<int> sortedArr = generateSortedVector(size);       // Best case
        vector<int> reversedArr = generateReversedVector(size);   // Worst case
        vector<int> randomArr = generateRandomVector(size);       // Average case

        // Bubble Sort
        bubbleTimes[i][0] = measureSortingTime(bubbleSort, sortedArr);
        bubbleTimes[i][1] = measureSortingTime(bubbleSort, reversedArr);
        bubbleTimes[i][2] = computeAverageTime(randomArr, bubbleSort);

        // Insertion Sort
        insertionTimes[i][0] = measureSortingTime(insertionSort, sortedArr);
        insertionTimes[i][1] = measureSortingTime(insertionSort, reversedArr);
        insertionTimes[i][2] = computeAverageTime(randomArr, insertionSort);

        // Selection Sort
        selectionTimes[i][0] = measureSortingTime(selectionSort, sortedArr);
        selectionTimes[i][1] = measureSortingTime(selectionSort, reversedArr);
        selectionTimes[i][2] = computeAverageTime(randomArr, selectionSort);

        // Merge Sort
        mergeTimes[i][0] = measureSortingTime(mergeSortWrapper, sortedArr);
        mergeTimes[i][1] = measureSortingTime(mergeSortWrapper, reversedArr);
        mergeTimes[i][2] = computeAverageTime(randomArr, mergeSortWrapper);

        // QuickSort - Random Pivot
        quickRandomTimes[i][0] = measureSortingTime(quickSortRandomPivotWrapper, sortedArr);
        quickRandomTimes[i][1] = measureSortingTime(quickSortRandomPivotWrapper, reversedArr);
        quickRandomTimes[i][2] = computeAverageTime(randomArr, quickSortRandomPivotWrapper);

        // QuickSort - Min Pivot
        quickMinTimes[i][0] = measureSortingTime(quickSortMinPivotWrapper, sortedArr);
        quickMinTimes[i][1] = measureSortingTime(quickSortMinPivotWrapper, reversedArr);
        quickMinTimes[i][2] = computeAverageTime(randomArr, quickSortMinPivotWrapper);

        // QuickSort - Max Pivot
        quickMaxTimes[i][0] = measureSortingTime(quickSortMaxPivotWrapper, sortedArr);
        quickMaxTimes[i][1] = measureSortingTime(quickSortMaxPivotWrapper, reversedArr);
        quickMaxTimes[i][2] = computeAverageTime(randomArr, quickSortMaxPivotWrapper);

        // QuickSort - Median of Medians Pivot
        quickMedianTimes[i][0] = measureSortingTime(quickSortMedianOfMediansWrapper, sortedArr);
        quickMedianTimes[i][1] = measureSortingTime(quickSortMedianOfMediansWrapper, reversedArr);
        quickMedianTimes[i][2] = computeAverageTime(randomArr, quickSortMedianOfMediansWrapper);
    }

    // Write results to CSV
    writeResultsToCSV("sorting_results.csv", sizes,
                      bubbleTimes, insertionTimes, selectionTimes, mergeTimes,
                      quickRandomTimes, quickMinTimes, quickMaxTimes, quickMedianTimes);
    cout << "Results written to 'sorting_results.csv'" << endl;

    for (size_t i = 0; i < sizes.size(); ++i) {
        cout << "Size: " << sizes[i] << endl;
        cout << "QuickSort-Random (Sorted): " << quickRandomTimes[i][0] << " seconds" << endl;
        cout << "QuickSort-Random (Reversed): " << quickRandomTimes[i][1] << " seconds" << endl;
        cout << "QuickSort-Random (Average): " << quickRandomTimes[i][2] << " seconds" << endl;
        cout << "QuickSort-Median (Sorted): " << quickMedianTimes[i][0] << " seconds" << endl;
        cout << "QuickSort-Median (Reversed): " << quickMedianTimes[i][1] << " seconds" << endl;
        cout << "QuickSort-Median (Average): " << quickMedianTimes[i][2] << " seconds" << endl;
    }
    return 0;
}
