# Huffman

Usage: 

```
./main input/file output/file huffman/file [c/x]
```

c is for compression
x for extraction

Example:

```
./main lorem.txt compressed.txt huffman.txt c
```

This will compress `lorem.txt` and generate two files: `compressed.txt` and `huffman.txt` 
The first one contains the compressed version of lorem.txt and the second one all the informations necessary in order to decompress it;


```
./main compressed.txt decompressed.txt huffman.txt x
```

This will extract `compressed.txt` using `huffman.txt` and will generate `decompressed.txt`
