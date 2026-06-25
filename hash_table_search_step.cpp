// *********************************************************
// Program: hash_table_search_step.cpp
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
    long long key; // stores the integer key
    string word; // stores the word beside the key
};

struct Node {
    Record data; // stores one record in the node
    Node* next; // points to the next node if collision happens
};

class HashTable {
private:
    vector<Node*> table; // hash table, each index points to a linked list
    int tableSize;  // total size of the hash table

public:
    HashTable(int size) {
        tableSize = size; // save table size
        table.assign(tableSize, NULL); // set all indexes as empty
    }

    ~HashTable() {
        clear(); // delete all nodes before program ends
    }

    int hashFunction(long long key) const {
        return key % tableSize; // get index using modulus
    }

    void insert(Record r) {
        int index = hashFunction(r.key); // find index for this key

        Node* newNode = new Node; // create new node
        newNode->data = r; // store record in node
        newNode->next = table[index]; // link to old first node

        table[index] = newNode; // put new node at the front
    }

    void searchStep(long long target, ofstream& out) const {
        int index = hashFunction(target); // find which index to search
        Node* current = table[index]; // start from first node at that index

        out << "target = " << target << "\n"; // Display target and index information
        out << "hash index = " << target << " % " << tableSize << " = " << index << "\n";
        out << "search path: ";

        bool first = true;

        while (current != NULL) { // Display every record checked during searching.
            if (first == false) {
                out << " -> "; // add arrow between checked records
            }

            out << current->data.key << "/" << current->data.word; // print current record
            first = false;

            if (current->data.key == target) { // Check whether the target is found.
                out << "\n";
                out << target << " = " << current->data.key << "/" << current->data.word << "\n";
                return; // stop searching because target is found
            }

            current = current->next; // move to next node in the chain
        }

        if (first == true) {
            out << "empty bucket"; // target is not found
        }

        out << "\n"; // Display not found message.
        out << "-1 != " << target << "\n";
    }

    void clear() { // delete all nodes from the hash table
        for (int i = 0; i < tableSize; i++) {
            Node* current = table[i];

            while (current != NULL) {
                Node* temp = current; // keep current node first
                current = current->next; // move to next node
                delete temp; // delete old node
            }

            table[i] = NULL; // make this index empty
        }
    }
};

vector<Record> readDataset(const string& filename) {
    vector<Record> a; // stores all records from the file
    ifstream inFile(filename.c_str()); // open dataset file
    string line; // stores one line from the file

    while (getline(inFile, line)) {
        if (line != "") {
            stringstream ss(line); // split the line
            string left; // stores key part
            string right; // stores word part

            if (getline(ss, left, ',') && getline(ss, right)) {
                Record r;
                r.key = stoll(left);  // convert key from string to long long
                r.word = right; // store word
                a.push_back(r); // add record into vector
            }
        }
    }

    return a; // return all records
}

string getSizeText(const string& filename, int n) {
    string text = ""; // stores numbers found in filename

    for (int i = 0; i < (int)filename.length(); i++) {
        if (filename[i] >= '0' && filename[i] <= '9') {
            text = text + filename[i]; // collect digits from filename
        }
    }

    if (text == "") {
        text = to_string(n); // use number of records if filename has no digit
    }

    return text; // return dataset size text
}

int main() {
    string filename;
    long long target;

    cout << "Enter dataset filename: ";
    cin >> filename;

    cout << "Enter target integer: ";
    cin >> target;

    vector<Record> records = readDataset(filename); // read data from file
    int n = records.size(); // get number of records


    if (n == 0) {
        cout << "No data loaded." << endl;
        return 1; // stop program if file is empty or not loaded
    }

    int tableSize = n / 10 + 1; // choose hash table size

    HashTable ht(tableSize); // create hash table

    for (int i = 0; i < n; i++) {
        ht.insert(records[i]); // insert every record into hash table
    }

    string sizeText = getSizeText(filename, n); // get size text for output filename
    string outName = "dataset_" + sizeText + "_hash_table_search_step_" + to_string(target) + ".txt";

    ofstream out(outName.c_str()); // create output file

    ht.searchStep(target, out); // write search steps into output file

    cout << "Step output written to " << outName << endl;

    return 0;
}
