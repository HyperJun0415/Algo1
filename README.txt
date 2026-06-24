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
./dataset_generator 1000
./radix_sort dataset_1000.csv
./radix_sort_step dataset_1000.csv 1 7
./heap_sort dataset_1000.csv
./heap_sort_step dataset_1000.csv 1 7
./hash_table_search dataset_1000.csv
./hash_table_search_step dataset_1000.csv 1000000038

Expected output file names:
dataset_n.csv
radix_sorted_dataset_n.csv
dataset_n_radix_sorted_step_startrow_endrow.txt
heap_sorted_dataset_n.csv
dataset_n_heap_sorted_step_startrow_endrow.txt
hash_table_search_dataset_n.txt
dataset_n_hash_table_search_step_target.txt


