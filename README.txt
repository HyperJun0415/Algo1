CCP6214 Algorithm Design & Analysis - Coding Files

Compile examples:
    g++ -std=c++11 dataset_generator.cpp -o dataset_generator
    g++ -std=c++11 radix_sort.cpp -o radix_sort
    g++ -std=c++11 radix_sort_step.cpp -o radix_sort_step
    g++ -std=c++11 heap_sort.cpp -o heap_sort
    g++ -std=c++11 heap_sort_step.cpp -o heap_sort_step
    g++ -std=c++11 hash_table_search.cpp -o hash_table_search
    g++ -std=c++11 hash_table_search_step.cpp -o hash_table_search_step

Run examples:
    ./dataset_generator 35000000
    ./radix_sort dataset_35000000.csv
    ./radix_sort_step dataset_35000000.csv 1 5
    ./heap_sort dataset_35000000.csv
    ./heap_sort_step dataset_35000000.csv 1 7
    ./hash_table_search dataset_35000000.csv
    ./hash_table_search_step dataset_35000000.csv 1000000038

Expected output file names:
    dataset_n.csv
    radix_sorted_dataset_n.csv
    dataset_n_radix_sorted_step_startrow_endrow.txt
    heap_sorted_dataset_n.csv
    dataset_n_heap_sorted_step_startrow_endrow.txt
    hash_table_search_dataset_n.txt
    dataset_n_hash_table_search_step_target.txt


Code explanation summary for documentation

Dataset generator
    The dataset generator creates n records in the form integer,string. The integer key is a 10-digit positive number. 
    The keys are generated uniquely and then shuffled using the Fisher-Yates method. 
    The string field is generated as 5 lowercase letters. The output file is named dataset_n.csv.

Radix sort
    The radix sort program sorts records according to the integer key. 
    It processes the digits from the rightmost digit to the leftmost digit. 
    Each digit pass uses counting sort, which keeps the sorting stable. 
    Since the integer field has 10 digits, the program performs 10 passes. 
    The normal program outputs radix_sorted_dataset_n.csv, 
        while the step program outputs dataset_n_radix_sorted_step_startrow_endrow.txt.

Heap sort
    The heap sort program sorts records according to the integer key using a max heap. First, the array is changed into a max heap. 
    Then the largest element at the root is swapped to the end of the array, and heapify is called again on the remaining heap. 
    The normal program outputs heap_sorted_dataset_n.csv, while the step program outputs dataset_n_heap_sorted_step_startrow_endrow.txt.

Hash table search
    The hash table uses the division method h(k) = k mod tableSize.
    Each table location stores a linked list to handle collisions by chaining. 
    Insertion adds the new node at the beginning of the linked list. 
    Searching hashes the target key and then compares the target with nodes in the selected linked list. 
    The normal program performs n searches for best, average, and worst cases. 
    The step program prints the hash index and search path for a selected target.

Complexities
    Radix sort time complexity is O(d(n + b)), where d is the number of digits and b is the base. 
    Here, d = 10 and b = 10, so it is close to O(n) for this fixed integer length. Space complexity is O(n + b).

    Heap sort time complexity is O(n log n) for best, average, and worst cases. S
    Pace complexity is O(1) extra space for the array-based version, except for small recursion stack usage in heapify.

    Hash table search has O(1) best case and average case when the data is distributed well and the load factor is controlled. 
    The worst case is O(n) if many keys collide into the same chain. Space complexity is O(n + tableSize).



