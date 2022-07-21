# Huffman Encoding Project

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

The compression is performed using the Huffman coding. Two binary files are used or generated:
- Compressed File: it is the original file, but each symbol is replace with its huffman encoding.
- Huffamn coding information: it is a file that is required by the decompressing algorithm in order to re-create the huffman codes.

File format:

```
padding | character | code length
```

This type of format is possible because Huffman canonical coding is used.

***

**Please note that this implementation is purely academic and can be optimized in terms of memory and cpu usage.**



# Encoding 
Huffman canonical coding is used. For generating this encoding the occurrences for each character are counted, and then, using the traditional Huffman algorithm encodings are generated. Unluckily these encodings are not (yet) canonical. For this reason, they have to be converted.

Starting from the characters, sorted by code length and alphabetically and implementing the following code, a canonical encoding is achieved.

```
uint64_t counter =0;
uint64_t old_bitlen = vector_encoding_length[0].second;

for (const auto &x : this->vector_encoding_length){
    counter = counter << (x.second - old_bitlen);
    this->encoding[x.first] = numberToBitString(counter,x.second);
    counter = (counter + 1);
    old_bitlen = x.second;
}
```

# Compression
For simplicity, the codes are strings of "0"s and "1"s and they are stored inside an `unordered_map<char,string>`. Thus to get the Huffman version of the text it is just necessary to iterate over the uncompressed text and substitute each char with the new encoding.

# Decompression
Starting from the Coding Information file, the canonical encoding is reconstructed using the same approach as before. A "reversed" `unordered_map<string,char>` was considered. To perform the actual decoding the following was used:

```
while(index < str_length) {
    uint32_t i;
    for(i=this->min_length_code; i < this->max_length_code+1; i++){

        auto search = this->encoding.find(encoded.substr(index,i));

        if(search != this->encoding.end()){
            decoded += search->second;
            index += search->first.length();
            break;
        }
    }
}
```

# Results:

| Filename        | File Size [bytes] | Huffman | gzip   | lzop   | bzip2  |
|-----------------|-----------|---------|--------|--------|--------|
| alice29.txt     | 152089    | 87911   | 54435  | 86846  | 43202  |
| asyoulik.txt    | 125179    | 76011   | 48951  | 76230  | 39569  |
| baddata1.snappy | 27512     | 25246   | 22936  | 27581  | 23802  |
| baddata2.snappy | 27483     | 25283   | 23016  | 27552  | 23900  |
| baddata3.snappy | 28384     | 26035   | 23721  | 28453  | 24572  |
| fireworks.jpeg  | 123093    | 123751  | 122942 | 123161 | 123118 |
| geo.protodata   | 118588    | 105972  | 15264  | 23857  | 14560  |
| html            | 102400    | 67393   | 13740  | 22525  | 12570  |
| html_x_4        | 409600    | 268750  | 53578  | 89770  | 16680  |
| kppkn.gtb       | 184320    | 59867   | 38737  | 71316  | 36351  |
| lcet10.txt      | 426754    | 250818  | 144885 | 234341 | 107706 |
| paper-100k.pdf  | 102400    | 98433   | 81259  | 85222  | 82980  |
| plrabn12.txt    | 481861    | 275829  | 195208 | 311294 | 145577 |
| urls.10K        | 702087    | 463779  | 223884 | 342073 | 164887 |


![alt text](https://i.imgur.com/KLBPlmp.png "Plotted Results")
