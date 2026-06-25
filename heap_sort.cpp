// *********************************************************
// Program: heap_sort.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC3L
// Tutorial Class: TT9L
// Trimester: 2610
// Member_1: 242UC244PB | LEM JOE ERN | lem.joe.ern@student.mmu.edu.my | 0162237965
// Member_2: 251UC250J5 | LEE JUN YAN | lee.jun.yan@student.mmu.edu.my | 0128500415
// Member_3: 251UC25141 | SHAWN GOH XUN SHEN | shawn.goh.xun@student.mmu.edu.my | 0199906601
// Member_4: 242UC244KV | KOH HUI WEN | koh.hui.wen@student.mmu.edu.my | 0129817286
// *********************************************************
// Task Distribution
// Member_1: Dataset Generator
// Member_2: Radix Sort
// Member_3: Heap Sort
// Member_4: Hash Table Search
// *********************************************************v

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
using namespace std;

// Core Data Structure
// Binds the integer (key) and the string (word) together in memory
struct Record {
    long long key;  // The 10-digit number used for sorting
    string word;    // The 5-letter string that tags along
};

// Data Loader
// Parses the million-row CSV file and loads it into working memory
vector<Record> readDataset(const string& filename) {
    vector<Record> a;
    ifstream inFile(filename.c_str());
    string line;

    // Read the file line-by-line until the end
    while (getline(inFile, line)) {
        if (line != "") {
            stringstream ss(line);
            string left;
            string right;

            // Split at the comma. Left is the number, Right is the word.
            if (getline(ss, left, ',') && getline(ss, right)) {
                Record r;
                r.key = stoll(left);    // stoll converts String TO Long Long
                r.word = right;
                a.push_back(r);         // Append the Record to the vector
            }
        }
    }
    return a;
}

// String Extractor Utility
// Pulls the numbers out of the input filename (e.g., gets "1000" out of "dataset_1000.csv")
// This ensures the output file is named correctly
string getSizeText(const string& filename, int n) {
    string text = "";

    for (int i = 0; i < (int)filename.length(); i++) {
        if (filename[i] >= '0' && filename[i] <= '9') {
            text = text + filename[i];
        }
    }

    if (text == "") {
        text = to_string(n);
    }

    return text;
}

// Swap Utility
// Swaps two entire records in the array. Since the struct is swapped
// the string 'word' is guaranteed to stay with its 'key'
void swapRecord(vector<Record>& a, int i, int j) {
    Record temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

// Max-Heap Maintenance (The Math Engine)
// Enforces the rule that a parent must be larger than its two children
void heapify(vector<Record>& a, int heapSize, int root) {
    int largest = root;
    int left = 2 * root + 1;    // Math to find left child index
    int right = 2 * root + 2;   // Math to find right child index

    // Check if left child exists within the active boundary AND is larger than the parent
    if (left < heapSize && a[left].key > a[largest].key) {
        largest = left;
    }

    // Check if right child exists AND is larger than the current largest
    if (right < heapSize && a[right].key > a[largest].key) {
        largest = right;
    }

    // If the parent is no longer the largest, demote it
    if (largest != root) {
        swapRecord(a, root, largest);
        // Recursively check the branch we just swapped into to ensure it didn't break rules below
        heapify(a, heapSize, largest);
    }
}

// The Main Sorting Algorithm
// Operates strictly in O(n log n) time and O(1) space.
void heapSort(vector<Record>& a) {
    int n = a.size();

    // Phase 1: Build the initial Max-Heap
    // Start at the last non-leaf node and work backward to the root
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }

    // Phase 2: Extract the maximum element one by one
    for (int i = n - 1; i > 0; i--) {
        // Swap the absolute largest number (at root 0) to its final resting place at the back (i)
        swapRecord(a, 0, i);
        // Shrink the active heap size by passing 'i' as the boundary, 
        // and let the new (small) root sift down to find the NEXT largest number
        heapify(a, i, 0);
    }
}

int main() {
    string filename;

    cout << "Enter dataset filename: ";
    cin >> filename;

    vector<Record> a = readDataset(filename);
    int n = a.size();

    if (n == 0) {
        cout << "No data loaded." << endl;
        return 1;
    }

    // Precision timing block
    // Start the clock exactly here, after the file is fully loaded into memory
    auto start = chrono::high_resolution_clock::now();

    heapSort(a);    // Run the algorithm

    // Stop the clock exactly here, before starts writing the output file
    auto stop = chrono::high_resolution_clock::now();

    // calculate the duration in seconds
    double seconds = chrono::duration<double>(stop - start).count();

    // output generation
    string sizeText = getSizeText(filename, n);
    string outName = "heap_sorted_dataset_" + sizeText + ".csv";

    ofstream outFile(outName.c_str());

    // write the newly sorted array out to the final CSV file
    for (int i = 0; i < n; i++) {
        outFile << a[i].key << "," << a[i].word << "\n";
    }

    outFile << "Running time: " << fixed << setprecision(9) << seconds << " seconds\n";

    // Print the strictly formatted floating point time to the terminal
    cout << fixed << setprecision(9);
    cout << "Heap sort running time: " << seconds << " seconds" << endl;
    cout << "Output written to " << outName << endl;

    return 0;
}
