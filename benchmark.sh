#/bin/bash

rm -f benchmark_results/*

#huffman
for filename in benchmark_files/*; do
    ./main ${filename} benchmark_files/compresso benchmark_files/huffman c

    original_size=$(wc -c ${filename} | awk '{print $1}') 

    compressed_size=$(wc -c benchmark_files/compresso | awk '{print $1}') 
    huffman_size=$(wc -c benchmark_files/huffman | awk '{print $1}') 
    total_compressed_size=$(($compressed_size + $huffman_size)) 

    rm -f benchmark_files/compresso benchmark_files/huffman
    echo $filename $original_size $total_compressed_size >> benchmark_results/huffman.txt

done

#gzip

for filename in benchmark_files/*; do
    gzip -k -c ${filename} > benchmark_files/compresso 

    original_size=$(wc -c ${filename} | awk '{print $1}') 

    compressed_size=$(wc -c benchmark_files/compresso | awk '{print $1}') 

    echo $filename $original_size $compressed_size >> benchmark_results/gzip.txt
    rm -f benchmark_files/compresso

done

#bzip

for filename in benchmark_files/*; do
    bzip2 -z -k -c ${filename} > benchmark_files/compresso 

    original_size=$(wc -c ${filename} | awk '{print $1}') 

    compressed_size=$(wc -c benchmark_files/compresso | awk '{print $1}') 

    echo $filename $original_size $compressed_size >> benchmark_results/bzip2.txt
    rm -f benchmark_files/compresso

done

#lzop

for filename in benchmark_files/*; do
    lzop -k -c ${filename} > benchmark_files/compresso 

    original_size=$(wc -c ${filename} | awk '{print $1}') 

    compressed_size=$(wc -c benchmark_files/compresso | awk '{print $1}') 

    echo $filename $original_size $compressed_size >> benchmark_results/lzop.txt
    rm -f benchmark_files/compresso

done