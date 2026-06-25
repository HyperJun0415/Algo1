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

struct Record
{
    long long key;
    string word;
};

vector<Record> readDataset(const string &filename)
{
    vector<Record> a;
    ifstream inFile(filename.c_str());
    string line;

    while (getline(inFile, line))
    {
        if (line != "")
        {
            stringstream ss(line);
            string left;
            string right;

            if (getline(ss, left, ',') && getline(ss, right))
            {
                Record r;
                r.key = stoll(left);
                r.word = right;
                a.push_back(r);
            }
        }
    }

    return a;
}

string getSizeText(const string &filename, int n)
{
    string text = "";

    for (int i = 0; i < (int)filename.length(); i++)
    {
        if (filename[i] >= '0' && filename[i] <= '9')
        {
            text = text + filename[i];
        }
    }

    if (text == "")
    {
        text = to_string(n);
    }

    return text;
}

void swapRecord(vector<Record> &a, int i, int j)
{
    Record temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

// Core structural maintenance routine. It compares a parent node with its
// left and right children to enforce Max-Heap property (which is: Parent >= Children).

void heapify(vector<Record> &a, int heapSize, int root)
{
    int largest = root;
    int left = 2 * root + 1;  // Binary tree left-child
    int right = 2 * root + 2; // Binary tree right-child

    if (left < heapSize && a[left].key > a[largest].key)
    {
        largest = left;
    }

    if (right < heapSize && a[right].key > a[largest].key)
    {
        largest = right;
    }

    // If a child is larger than the root, swap them. Then, call heapify downwards
    // to fix any ripple effects the swap caused in the lower sub-trees.

    if (largest != root)
    {
        swapRecord(a, root, largest);
        heapify(a, heapSize, largest);
    }
}

void heapSort(vector<Record> &a)
{
    int n = a.size();

    // Phase 1: Build Max-Heap.
    // We start at 'n/2 - 1' because all nodes beyond that are leaf nodes
    // (they don't have children to heapify). This phase takes O(n) time.

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(a, n, i);
    }

    // Phase 2: Sorting phase.
    // Largest element always sit at index 0. We swap it to the end of the array
    // (index i), shrink the active heap size boundary, and restore the max-heap.
    // This phase runs (n-1) times, executing an O(log n) heapify each time, giving us O(n log n).

    for (int i = n - 1; i > 0; i--)
    {
        swapRecord(a, 0, i);
        heapify(a, i, 0);
    }
}

int main()
{
    string filename;

    cout << "Enter dataset filename: ";
    cin >> filename;

    vector<Record> a = readDataset(filename);
    int n = a.size();

    if (n == 0)
    {
        cout << "No data loaded." << endl;
        return 1;
    }

    // Isolate calculation logic from I/O boundaries. High-resolution clock
    // captures CPU cycles exclusively during the sort execution to keep metrics accurate.

    auto start = chrono::high_resolution_clock::now();

    heapSort(a);

    auto stop = chrono::high_resolution_clock::now();

    double seconds = chrono::duration<double>(stop - start).count();

    string sizeText = getSizeText(filename, n);
    string outName = "heap_sorted_dataset_" + sizeText + ".csv";

    ofstream outFile(outName.c_str());

    for (int i = 0; i < n; i++)
    {
        outFile << a[i].key << "," << a[i].word << "\n";
    }

    outFile << "Running time: " << fixed << setprecision(9) << seconds << " seconds\n";

    cout << fixed << setprecision(9);
    cout << "Heap sort running time: " << seconds << " seconds" << endl;
    cout << "Output written to " << outName << endl;

    return 0;
}
