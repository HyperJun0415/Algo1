// *********************************************************
// Program: heap_sort_step.cpp
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
// *********************************************************

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// This binds the integer key and the string word together.
// When the keys are swapped during sorting, the word follows its key automatically.
struct Record {
    long long key;
    string word;
};

// This function reads the comma-separated values from your dataset.
vector<Record> readDataset(const string& filename) {
    vector<Record> a;
    ifstream inFile(filename.c_str());
    string line;

    // Read the file line by line
    while (getline(inFile, line)) {
        if (line != "") {
            stringstream ss(line);
            string left;
            string right;

            // Split the line at the comma (',')
            if (getline(ss, left, ',') && getline(ss, right)) {
                Record r;
                r.key = stoll(left);    // Convert the string number to a long long integer
                r.word = right;         // Keep the 5-letter word as a string
                a.push_back(r);         // Add the record to the vector array
            }
        }
    }
    return a;
}

// This extracts the number from names like "dataset_1000.csv" to use in the output filename.
string getSizeText(const string& filename, int n) {
    string text = "";

    for (int i = 0; i < (int)filename.length(); i++) {
        // If the character is a digit, add it to our text string
        if (filename[i] >= '0' && filename[i] <= '9') {
            text = text + filename[i];
        }
    }

    // Fallback if no numbers were in the filename
    if (text == "") {
        text = to_string(n);
    }

    return text;
}

// This is custom to the "step" file. It formats the array like [key/word, key/word] 
// and adds the label (like "initial" or "i = 6") at the end.
void printArray(ofstream& out, const vector<Record>& a, const string& label) {
    out << "[";

    for (int i = 0; i < (int)a.size(); i++) {
        out << a[i].key << "/" << a[i].word;

        if (i != (int)a.size() - 1) {
            out << ", ";
        }
    }
    out << "] " << label << "\n";
}

// Swap Utility
void swapRecord(vector<Record>& a, int i, int j) {
    Record temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

// This enforces the rule: A parent node must be larger than its children.
void heapify(vector<Record>& a, int heapSize, int root) {
    int largest = root;
    // Calculate the array indices of the left and right children
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    // If the left child is within the active heap and is larger than the parent
    if (left < heapSize && a[left].key > a[largest].key) {
        largest = left;
    }

    // If the right child is within the active heap and is larger than the current largest
    if (right < heapSize && a[right].key > a[largest].key) {
        largest = right;
    }

    // If one of the children was larger than the original root
    if (largest != root) {
        swapRecord(a, root, largest);   // Swap
        // Recursively check the affected branch to ensure the swap didn't break rules further down
        heapify(a, heapSize, largest);
    }
}

int main() {
    string filename;
    int startRow;
    int endRow;

    // Get User Inputs
    cout << "Enter dataset filename: ";
    cin >> filename;

    cout << "Enter start row: ";
    cin >> startRow;

    cout << "Enter end row: ";
    cin >> endRow;

    // Load ALL data from the CSV into memory
    vector<Record> all = readDataset(filename);

    // Input validation to prevent crashes
    if (startRow < 1) {
        startRow = 1;
    }

    if (endRow > (int)all.size()) {
        endRow = all.size();
    }

    if (startRow > endRow) {
        cout << "Invalid row range." << endl;
        return 1;
    }

    // Extract the Subset
    vector<Record> a;

    for (int i = startRow - 1; i <= endRow - 1; i++) {
        a.push_back(all[i]);    // Copy only the requested rows into a new array 'a'
    }

    // Prepare the output text file name
    string sizeText = getSizeText(filename, all.size());
    string outName = "dataset_" + sizeText + "_heap_sorted_step_" + to_string(startRow) + "_" + to_string(endRow) + ".txt";

    ofstream out(outName.c_str());

    int n = a.size();

    // Phase 1: Builds initial max heap
    // Loop backward from the middle of the array to the start
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }

    // Print the array state after the Max-Heap is successfully built
    printArray(out, a, "initial");

    // Phase 2: Extract and sort
    // The largest number is currently at index 0. 
    for (int i = n - 1; i > 0; i--) {
        // Swap the largest number to the current end of the active array
        swapRecord(a, 0, i);

        // The array is now 'broken' because a small number is at the root
        // Call heapify to let that small number sink down, bringing the NEXT largest number to the top
        // Then pass 'i' as the heapSize. This shrinks the active heap, ignoring the sorted numbers at the back
        heapify(a, i, 0);
        // Print the array state after the new largest number has surfaced
        printArray(out, a, "i = " + to_string(i));
    }

    cout << "Step output written to " << outName << endl;

    return 0;
}
