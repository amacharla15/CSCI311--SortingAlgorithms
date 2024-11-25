#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
using namespace std;

void readCSV(const string& filename, vector<int>& sizes,
             vector<vector<double>>& bubbleTimes,
             vector<vector<double>>& insertionTimes,
             vector<vector<double>>& selectionTimes,
             vector<vector<double>>& mergeTimes,
             vector<vector<double>>& quickRandomTimes,
             vector<vector<double>>& quickMinTimes,
             vector<vector<double>>& quickMaxTimes,
             vector<vector<double>>& quickMedianTimes) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    getline(file, line); // Skip the header

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        int size;
        string algorithm, caseType;
        double time;

        try {
            // Parse the CSV line
            getline(ss, token, ',');
            size = stoi(token);  // Parse size
            getline(ss, token, ',');
            algorithm = token;  // Parse algorithm
            getline(ss, token, ',');
            caseType = token;   // Parse case
            getline(ss, token, ',');
            time = stod(token); // Parse time

            // Find the index corresponding to the size
            int idx = find(sizes.begin(), sizes.end(), size) - sizes.begin();
            if (idx >= sizes.size()) {
                cerr << "Warning: Size " << size << " not found in predefined sizes. Skipping line: " << line << endl;
                continue;
            }

            // Store the timing data based on algorithm and case
            if (algorithm == "Bubble Sort") {
                if (caseType == "Sorted") bubbleTimes[idx][0] = time;
                else if (caseType == "Reversed") bubbleTimes[idx][1] = time;
                else if (caseType == "Average") bubbleTimes[idx][2] = time;
            } else if (algorithm == "Insertion Sort") {
                if (caseType == "Sorted") insertionTimes[idx][0] = time;
                else if (caseType == "Reversed") insertionTimes[idx][1] = time;
                else if (caseType == "Average") insertionTimes[idx][2] = time;
            } else if (algorithm == "Selection Sort") {
                if (caseType == "Sorted") selectionTimes[idx][0] = time;
                else if (caseType == "Reversed") selectionTimes[idx][1] = time;
                else if (caseType == "Average") selectionTimes[idx][2] = time;
            } else if (algorithm == "Merge Sort") {
                if (caseType == "Sorted") mergeTimes[idx][0] = time;
                else if (caseType == "Reversed") mergeTimes[idx][1] = time;
                else if (caseType == "Average") mergeTimes[idx][2] = time;
            } else if (algorithm == "QuickSort-Random") {
                if (caseType == "Sorted") quickRandomTimes[idx][0] = time;
                else if (caseType == "Reversed") quickRandomTimes[idx][1] = time;
                else if (caseType == "Average") quickRandomTimes[idx][2] = time;
            } else if (algorithm == "QuickSort-Min") {
                if (caseType == "Sorted") quickMinTimes[idx][0] = time;
                else if (caseType == "Reversed") quickMinTimes[idx][1] = time;
                else if (caseType == "Average") quickMinTimes[idx][2] = time;
            } else if (algorithm == "QuickSort-Max") {
                if (caseType == "Sorted") quickMaxTimes[idx][0] = time;
                else if (caseType == "Reversed") quickMaxTimes[idx][1] = time;
                else if (caseType == "Average") quickMaxTimes[idx][2] = time;
            } else if (algorithm == "QuickSort-Median") {
                if (caseType == "Sorted") quickMedianTimes[idx][0] = time;
                else if (caseType == "Reversed") quickMedianTimes[idx][1] = time;
                else if (caseType == "Average") quickMedianTimes[idx][2] = time;
            }
        } catch (const std::exception& e) {
            cerr << "Error parsing line: " << line << " (" << e.what() << ")" << endl;
            continue; // Skip malformed lines
        }
    }

    file.close();
}

void plotResults(const vector<int>& sizes,
                 const vector<vector<double>>& bubbleTimes,
                 const vector<vector<double>>& insertionTimes,
                 const vector<vector<double>>& selectionTimes,
                 const vector<vector<double>>& mergeTimes,
                 const vector<vector<double>>& quickRandomTimes,
                 const vector<vector<double>>& quickMinTimes,
                 const vector<vector<double>>& quickMaxTimes,
                 const vector<vector<double>>& quickMedianTimes) {
    vector<double> sizesDouble(sizes.begin(), sizes.end());

    // Extract data for each case (sorted, reversed, average)
    vector<double> bubbleSorted, bubbleReversed, bubbleAverage;
    vector<double> insertionSorted, insertionReversed, insertionAverage;
    vector<double> selectionSorted, selectionReversed, selectionAverage;
    vector<double> mergeSorted, mergeReversed, mergeAverage;
    vector<double> quickRandomSorted, quickRandomReversed, quickRandomAverage;
    vector<double> quickMinSorted, quickMinReversed, quickMinAverage;
    vector<double> quickMaxSorted, quickMaxReversed, quickMaxAverage;
    vector<double> quickMedianSorted, quickMedianReversed, quickMedianAverage;

    for (const auto& row : bubbleTimes) {
        bubbleSorted.push_back(row[0]);
        bubbleReversed.push_back(row[1]);
        bubbleAverage.push_back(row[2]);
    }
    for (const auto& row : insertionTimes) {
        insertionSorted.push_back(row[0]);
        insertionReversed.push_back(row[1]);
        insertionAverage.push_back(row[2]);
    }
    for (const auto& row : selectionTimes) {
        selectionSorted.push_back(row[0]);
        selectionReversed.push_back(row[1]);
        selectionAverage.push_back(row[2]);
    }
    for (const auto& row : mergeTimes) {
        mergeSorted.push_back(row[0]);
        mergeReversed.push_back(row[1]);
        mergeAverage.push_back(row[2]);
    }
    for (const auto& row : quickRandomTimes) {
        quickRandomSorted.push_back(row[0]);
        quickRandomReversed.push_back(row[1]);
        quickRandomAverage.push_back(row[2]);
    }
    for (const auto& row : quickMinTimes) {
        quickMinSorted.push_back(row[0]);
        quickMinReversed.push_back(row[1]);
        quickMinAverage.push_back(row[2]);
    }
    for (const auto& row : quickMaxTimes) {
        quickMaxSorted.push_back(row[0]);
        quickMaxReversed.push_back(row[1]);
        quickMaxAverage.push_back(row[2]);
    }
    for (const auto& row : quickMedianTimes) {
        quickMedianSorted.push_back(row[0]);
        quickMedianReversed.push_back(row[1]);
        quickMedianAverage.push_back(row[2]);
    }

     Plot sorting results
    plt::figure();


    plt::plot(sizesDouble, bubbleSorted, {{"label", "Bubble Sort - Sorted"}});
    plt::plot(sizesDouble, bubbleReversed, {{"label", "Bubble Sort - Reversed"}});
    plt::plot(sizesDouble, bubbleAverage, {{"label", "Bubble Sort - Average"}});

    plt::plot(sizesDouble, insertionSorted, {{"label", "Insertion Sort - Sorted"}});
    plt::plot(sizesDouble, insertionReversed, {{"label", "Insertion Sort - Reversed"}});
    plt::plot(sizesDouble, insertionAverage, {{"label", "Insertion Sort - Average"}});

    plt::plot(sizesDouble, selectionSorted, {{"label", "Selection Sort - Sorted"}});
    plt::plot(sizesDouble, selectionReversed, {{"label", "Selection Sort - Reversed"}});
    plt::plot(sizesDouble, selectionAverage, {{"label", "Selection Sort - Average"}});


    

    plt::plot(sizesDouble, mergeSorted, {{"label", "Merge Sort - Sorted"}});
    plt::plot(sizesDouble, mergeReversed, {{"label", "Merge Sort - Reversed"}});
    plt::plot(sizesDouble, mergeAverage, {{"label", "Merge Sort - Average"}});

    
    plt::plot(sizesDouble, quickRandomSorted, {{"label", "QuickSort Random - Sorted"}});
    plt::plot(sizesDouble, quickRandomReversed, {{"label", "QuickSort Random - Reversed"}});
    plt::plot(sizesDouble, quickRandomAverage, {{"label", "QuickSort Random - Average"}});

    plt::plot(sizesDouble, quickMinSorted, {{"label", "QuickSort Min - Sorted"}});
    plt::plot(sizesDouble, quickMinReversed, {{"label", "QuickSort Min - Reversed"}});
    plt::plot(sizesDouble, quickMinAverage, {{"label", "QuickSort Min - Average"}});

    plt::plot(sizesDouble, quickMaxSorted, {{"label", "QuickSort Max - Sorted"}});
    plt::plot(sizesDouble, quickMaxReversed, {{"label", "QuickSort Max - Reversed"}});
    plt::plot(sizesDouble, quickMaxAverage, {{"label", "QuickSort Max - Average"}});

    plt::plot(sizesDouble, quickMedianSorted, {{"label", "QuickSort Median - Sorted"}});
    plt::plot(sizesDouble, quickMedianReversed, {{"label", "QuickSort Median - Reversed"}});
    plt::plot(sizesDouble, quickMedianAverage, {{"label", "QuickSort Median - Average"}});
    
    

    plt::xlabel("Array Size");
    plt::ylabel("Time (seconds)");
    plt::title("Sorting Algorithm Performance Comparison");
    plt::legend();
    plt::save("/mnt/c/Users/amacharla/project2/sorting_results.png");

    try {
        plt::show();
    } catch (const std::exception& e) {
        cerr << "Error displaying plot: " << e.what() << endl;
    }
}

int main() {
    vector<int> sizes = {10, 100, 1000, 10000};
    vector<vector<double>> bubbleTimes(sizes.size(), vector<double>(3, 0.0));
    vector<vector<double>> insertionTimes(sizes.size(), vector<double>(3, 0.0));
    vector<vector<double>> selectionTimes(sizes.size(), vector<double>(3, 0.0));
    vector<vector<double>> mergeTimes(sizes.size(), vector<double>(3, 0.0));
    vector<vector<double>> quickRandomTimes(sizes.size(), vector<double>(3, 0.0));
    vector<vector<double>> quickMinTimes(sizes.size(), vector<double>(3, 0.0));
    vector<vector<double>> quickMaxTimes(sizes.size(), vector<double>(3, 0.0));
    vector<vector<double>> quickMedianTimes(sizes.size(), vector<double>(3, 0.0));

    readCSV("sorting_results.csv", sizes, bubbleTimes, insertionTimes, selectionTimes, mergeTimes, quickRandomTimes, quickMinTimes, quickMaxTimes, quickMedianTimes);
    plotResults(sizes, bubbleTimes, insertionTimes, selectionTimes, mergeTimes, quickRandomTimes, quickMinTimes, quickMaxTimes, quickMedianTimes);

    return 0;
}
