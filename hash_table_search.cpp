// *********************************************************
// Program: hash_table_search.cpp
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
#include <chrono>
#include <iomanip>
using namespace std;

struct Record { // Structure to hold a single row of data
    long long key; //use long long for 10 digit integer
    string word;
};

struct Node { //single node inside the linked list for handling hash collisions
    Record data; // Holds the actual record data e.g key and word
    Node* next; // Pointer to the next node in the list
};

class HashTable {
private:
    vector<Node*> table; // The actual hash table that is an array of linked list pointers
    int tableSize; // Holds the total capacity of the hash table

public:
    HashTable(int size) { //constructor when table is created
        tableSize = size; // Set the table size
        table.assign(tableSize, NULL); // Fill the table with NULL to show it's currently empty
    }

    ~HashTable() { //deconstructor when table is destroyed to free up memory
        clear(); //call function to delete all nodes
    }

    int hashFunction(long long key) const { // Calculate hash table index using modulus operation
        return key % tableSize; // formula is key % tableSize
    }

    void insert(Record r) { // Inserts a new record into the hash table
        int index = hashFunction(r.key); // Calculate the index for this record.

        Node* newNode = new Node; // Create a new node.
        newNode->data = r; // Store the record inside the node.
        newNode->next = table[index]; // Link the new node to the current node.

        table[index] = newNode; // Insert the node into the hash table.
    }

    bool search(long long target, Record& found) const { // Searches for a target key. Returns true if found, false if not.
        int index = hashFunction(target); // Calculate the index of the target key.
        Node* current = table[index]; // Start searching from the first node.

        while (current != NULL) { // Continue searching until the end of the linked list.
            if (current->data.key == target) { // Compare the target key with the current key
                found = current->data; // Store the found record.
                return true;
            }

            current = current->next; // Move to the next node.
        }

        return false; // Target key not found.
    }

    // find the first key that exists in the hash table
    long long firstKeyInTable() const {
        for (int i = 0; i < tableSize; i++) {
            if (table[i] != NULL) {
                return table[i]->data.key; // return the first key found
            }
        }

        return -1; // return -1 if the table is empty
    }

    long long missingKeyForLongestChain() const {  // Find the longest linked list in the hash table
        int longestIndex = 0;
        int longest = -1;

        for (int i = 0; i < tableSize; i++) {
            int count = 0;  // count nodes at this index
            Node* current = table[i]; // start from the first node

            while (current != NULL) { // Count the number of nodes.
                count++; // add 1 for each node
                current = current->next; // move to next node
            }

            if (count > longest) { // Save the longest linked list.
                longest = count; // save the longest chain length
                longestIndex = i; // save the index of that chain
            }
        }

        long long target = 10000000000LL + longestIndex; // create a missing key for worst case search

        while (target % tableSize != longestIndex) { // Make sure the key is mapped to the same index.
            target++; // adjust the key until it maps to the longest chain index
        }

        return target;
    }

    void clear() { // delete all nodes from the hash table
        for (int i = 0; i < tableSize; i++) {
            Node* current = table[i];

            while (current != NULL) {
                Node* temp = current; // keep current node first
                current = current->next;  // move to next node
                delete temp; // delete old node
            }

            table[i] = NULL; // make this index empty
        }
    }
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

int main() {
    string filename;

    cout << "Enter dataset filename: ";
    cin >> filename;

    vector<Record> records = readDataset(filename);
    int n = records.size();

    if (n == 0) {
        cout << "No data loaded." << endl;
        return 1;
    }

    int tableSize = n / 10 + 1;

    HashTable ht(tableSize);

    for (int i = 0; i < n; i++) {
        ht.insert(records[i]);
    }

    Record found;
    volatile long long check = 0; //so the compiler does not ignore the search result

    long long bestTarget = ht.firstKeyInTable(); // key used for best case search
    long long worstTarget = ht.missingKeyForLongestChain(); // missing key used for worst case search

    // Best Case: search the same key that can be found quickly
    auto startBest = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        if (ht.search(bestTarget, found)) {
            check = check + found.key;
        }
    }

    auto stopBest = chrono::high_resolution_clock::now();

    // Average Case: search every key from the dataset
    auto startAverage = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        if (ht.search(records[i].key, found)) {
            check = check + found.key;
        }
    }

    auto stopAverage = chrono::high_resolution_clock::now();

    // Worst Case: search a missing key at the longest chain
    auto startWorst = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        if (ht.search(worstTarget, found)) {
            check = check + found.key;
        }
    }

    auto stopWorst = chrono::high_resolution_clock::now();

    // Calculate time differences in seconds
    double bestTime = chrono::duration<double>(stopBest - startBest).count();
    double averageTime = chrono::duration<double>(stopAverage - startAverage).count();
    double worstTime = chrono::duration<double>(stopWorst - startWorst).count();

    // Format output files based on dataset size
    string sizeText = getSizeText(filename, n);
    string outName = "hash_table_search_dataset_" + sizeText + ".txt";

    ofstream outFile(outName.c_str());

    // Write timing results to output log file
    outFile << fixed << setprecision(9);
    outFile << "Best case time: " << bestTime << " seconds\n";
    outFile << "Average case time: " << averageTime << " seconds\n";
    outFile << "Worst case time: " << worstTime << " seconds\n";
    outFile << "Number of searches per case: " << n << "\n";
    outFile << "Hash table size: " << tableSize << "\n";
    outFile << "Check value: " << check << "\n";

    // Print timing results
    cout << fixed << setprecision(9);
    cout << "Best case time: " << bestTime << " seconds" << endl;
    cout << "Average case time: " << averageTime << " seconds" << endl;
    cout << "Worst case time: " << worstTime << " seconds" << endl;
    cout << "Output written to " << outName << endl;

    return 0;
}
