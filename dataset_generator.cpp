// *********************************************************
// Program: dataset_generator.cpp
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

// Group leader ID 251UC250J5 is converted to seed 2511325005

#include <iostream>  
#include <fstream>   
#include <random>    
#include <string>    
#include <vector>    
using namespace std;

// This function generates a random 5-letter lowercase string.
// The generated string is used as the second field in each CSV record.
string generate_random_string(mt19937_64 &rng)
{
    // Generate a random number from 0 to 25.
    // 0 represents 'a', 1 represents 'b', ..., 25 represents 'z'.
    uniform_int_distribution<int> dist(0, 25);

    string str = "";

    // Repeat 5 times to create exactly 5 lowercase letters.
    for (int i = 0; i < 5; ++i)
    {
        str += (char)('a' + dist(rng));
    }

    return str;
}

int main()
{
    // Ask the user to enter how many records should be generated.
    // For example, if the user enters 1000, the program will generate 1000 records.
    long long n;
    cout << "Enter the dataset size (n): ";

    // Check whether the input is valid.
    // If the input is not a number or n is less than or equal to 0,
    // the program will display an error message and stop.
    if (!(cin >> n) || n <= 0)
    {
        cerr << "Invalid input size." << endl;
        return 1;
    }

    // Use a fixed seed based on the group leader student ID.
    // This makes the random output reproducible for testing and demonstration.
    unsigned long long seed = 2511325005ULL;
    mt19937_64 rng(seed);

    // Create the output file name based on the dataset size.
    // Example: if n = 1000, the filename becomes dataset_1000.csv.
    string filename = "dataset_" + to_string(n) + ".csv";
    ofstream outfile(filename);

    // Check whether the CSV file is created successfully.
    // If the file cannot be created, the program will display an error message and stop.
    if (!outfile.is_open())
    {
        cerr << "Error: Could not create file " << filename << endl;
        return 1;
    }

    cout << "Generating " << n << " unique randomized elements... Please wait." << endl;

    // The valid 10-digit integer range is from 1,000,000,000 to 9,999,999,999.
    // The range is divided into blocks to help avoid duplicate numbers.
    unsigned long long total_range = 8999999999ULL;
    unsigned long long stride = total_range / n;

    // If the dataset size is very large, stride may become 0.
    // This safeguard prevents division or modulo problems.
    if (stride == 0)
        stride = 1;

    // Create a vector to store all generated 10-digit integer keys.
    // The keys are stored first because they need to be shuffled before writing to the CSV file.
    vector<unsigned long long> keys;

    // reserve(n) prepares enough memory space for n keys before adding them.
    // This improves efficiency because the vector does not need to resize many times.
    keys.reserve(n);

    // Generate one random integer from each block.
    // Since each block is different, the generated keys are unique.
    for (long long i = 0; i < n; ++i)
    {
        // bucket_start is the starting value of the current block.
        unsigned long long bucket_start = 1000000000ULL + (i * stride);

        // random_offset adds randomness inside the current block.
        unsigned long long random_offset = rng() % stride;

        // The final key is stored inside the keys vector.
        keys.push_back(bucket_start + random_offset);
    }

    // Shuffle the keys so the dataset is not already sorted.
    // This makes the dataset random before sorting algorithms use it.
    // The shuffle used here is the Fisher-Yates shuffle.
    for (long long i = n - 1; i > 0; --i)
    {
        // Choose a random position j from 0 to i.
        uniform_int_distribution<long long> dist_shuffle(0, i);
        long long j = dist_shuffle(rng);

        // Swap keys[i] with keys[j].
        unsigned long long temp = keys[i];
        keys[i] = keys[j];
        keys[j] = temp;
    }

    // Write each record into the CSV file in the format: integer,string.
    // keys[i] is the unique 10-digit integer.
    // generate_random_string(rng) creates the random 5-letter lowercase string.
    // "\n" moves to the next line after writing each record.
    for (long long i = 0; i < n; ++i)
    {
        outfile << keys[i] << "," << generate_random_string(rng) << "\n";
    }

    outfile.close();

    cout << "Successfully generated " << filename << endl;

    return 0;
}
