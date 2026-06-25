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

struct Record {
    long long key;
    string word;
};

vector<Record> readDataset(const string& filename) {
    vector<Record> a;
    ifstream inFile(filename.c_str());
    string line;

    while (getline(inFile, line)) {
        if (line != "") {
            stringstream ss(line);
            string left;
            string right;

            if (getline(ss, left, ',') && getline(ss, right)) {
                Record r;
                r.key = stoll(left);
                r.word = right;
                a.push_back(r);
            }
        }
    }

    return a;
}

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

void swapRecord(vector<Record>& a, int i, int j) {
    Record temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void heapify(vector<Record>& a, int heapSize, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < heapSize && a[left].key > a[largest].key) {
        largest = left;
    }

    if (right < heapSize && a[right].key > a[largest].key) {
        largest = right;
    }

    if (largest != root) {
        swapRecord(a, root, largest);
        heapify(a, heapSize, largest);
    }
}

int main() {
    string filename;
    int startRow;
    int endRow;

    cout << "Enter dataset filename: ";
    cin >> filename;

    cout << "Enter start row: ";
    cin >> startRow;

    cout << "Enter end row: ";
    cin >> endRow;

    vector<Record> all = readDataset(filename);

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

    vector<Record> a;

    for (int i = startRow - 1; i <= endRow - 1; i++) {
        a.push_back(all[i]);
    }

    string sizeText = getSizeText(filename, all.size());
    string outName = "dataset_" + sizeText + "_heap_sorted_step_" + to_string(startRow) + "_" + to_string(endRow) + ".txt";

    ofstream out(outName.c_str());

    int n = a.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }

    printArray(out, a, "initial");

    for (int i = n - 1; i > 0; i--) {
        swapRecord(a, 0, i);
        heapify(a, i, 0);
        printArray(out, a, "i = " + to_string(i));
    }

    cout << "Step output written to " << outName << endl;

    return 0;
}
