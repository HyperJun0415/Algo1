// *********************************************************
// Program: dataset_generator.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC3L
// Tutorial Class: TT9L
// Trimester: 2610
// Member_1: 242UC244PB | LEM JOE ERN | lem.joe.ern@student.mmu.edu.my | 0162237965
// Member_2: ID | NAME | EMAIL | PHONE
// Member_3: ID | NAME | EMAIL | PHONE
// Member_4: 242UC244KV | KOH HUI WEN | koh.hui.wen@student.mmu.edu.my | 0129817286
// *********************************************************
// Task Distribution
// Member_1: Dataset Generator
// Member_2: Radix Sort
// Member_3: Heap Sort
// Member_4: Hash Table Search
// *********************************************************

// 251UC250J5 to 2511325005U seed
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
using namespace std;

// Function to generate a random 5-letter lowercase string
string generate_random_string(mt19937_64 &rng)
{
    uniform_int_distribution<int> dist(0, 25);
    string str = "";
    for (int i = 0; i < 5; ++i)
    {
        str += (char)('a' + dist(rng));
    }
    return str;
}

int main()
{
    long long n;
    cout << "Enter the dataset size (n): ";
    if (!(cin >> n) || n <= 0)
    {
        cerr << "Invalid input size." << endl;
        return 1;
    }

    // Requirement 5: Seed the 64-bit Mersenne Twister with your specific ID mapping
    unsigned long long seed = 2511325005ULL;
    mt19937_64 rng(seed);

    // Construct output filename dynamically, e.g., dataset_1000.csv
    string filename = "dataset_" + to_string(n) + ".csv";
    ofstream outfile(filename);

    if (!outfile.is_open())
    {
        cerr << "Error: Could not create file " << filename << endl;
        return 1;
    }

    cout << "Generating " << n << " unique randomized elements... Please wait." << endl;

    // Total available range: 9,999,999,999 - 1,000,000,000 = 8,999,999,999
    unsigned long long total_range = 8999999999ULL;
    unsigned long long stride = total_range / n;
    if (stride == 0)
        stride = 1; // Safeguard for exceptionally massive n

    // Step 1: Generate mathematically unique blocks across the full 10-digit range
    vector<unsigned long long> keys;
    keys.reserve(n); // Pre-allocate memory efficiently

    for (long long i = 0; i < n; ++i)
    {
        unsigned long long bucket_start = 1000000000ULL + (i * stride);
        unsigned long long random_offset = rng() % stride;
        keys.push_back(bucket_start + random_offset);
    }

    // Step 2: Fisher-Yates Shuffle to make the unique keys completely out of order
    // This ensures requirement 3c ("elements should be in random order before sorting") is met perfectly!
    for (long long i = n - 1; i > 0; --i)
    {
        uniform_int_distribution<long long> dist_shuffle(0, i);
        long long j = dist_shuffle(rng);

        // Swap elements
        unsigned long long temp = keys[i];
        keys[i] = keys[j];
        keys[j] = temp;
    }

    // Step 3: Stream directly to the CSV file paired with random strings
    for (long long i = 0; i < n; ++i)
    {
        outfile << keys[i] << "," << generate_random_string(rng) << "\n";
    }

    outfile.close();
    cout << "Successfully generated " << filename << endl;

    return 0;
}