# 📦 Compresso — Huffman File Compression Tool (C++)

Compresso is a **lossless file compression and decompression tool** written in **C++17**, built around the **Huffman Coding algorithm** with **custom bit-level I/O**. It is designed as a systems-level project that correctly handles **binary files** and **very large inputs (GB-scale)**.

---

## 🚀 Features

* Lossless compression using **Huffman Coding**
* Works with **text and binary files**
* Efficient **bit-level encoding** (no ASCII `0`/`1` waste)
* Handles **large files (tested with multi-GB inputs)**
* Self-describing compressed file format
* Preserves and restores **original file extension**
* Robust error handling and edge-case support
* Clean, modular C++ design (`.h` / `.cpp` separation)

---

## 🧠 How It Works

### Compression

1. Scan input file to build a **frequency table** (256 byte values)
2. Construct a **Huffman Tree** using a min-heap
3. Generate **prefix-free binary codes** using DFS
4. Write a file header containing metadata
5. Encode file contents using a custom **BitWriter**

### Decompression

1. Read and validate the file header
2. Rebuild the Huffman Tree from the frequency table
3. Decode bits using a **BitReader** and tree traversal
4. Stop decoding after the original file size is restored

---

## 📂 Project Structure

```
.
├── main.cpp
├── compress.cpp
├── decompress.cpp
├── frequency_table.cpp
├── huffman.cpp
├── BIT_IO.cpp
├── frequency_table.h
├── huffman.h
├── BIT_IO.h
└── README.md
```

---

## 📦 Compressed File Format

```
[MAGIC "HUF1"]           4 bytes
[ORIGINAL_FILE_SIZE]    8 bytes
[EXTENSION_LENGTH]      4 bytes
[EXTENSION]             N bytes
[FREQUENCY_TABLE]       256 × uint64_t
[COMPRESSED BITSTREAM]  variable
```

This design ensures:

* Correct tree reconstruction
* Safe handling of padding bits
* Automatic restoration of the original file extension

---

## 🔧 Build Instructions

### Requirements

* GCC / G++ with **C++17 support**
* Linux or macOS (developed and tested on Linux)

### Compile

```bash
g++ -std=c++17 -Wall -Wextra -g \
    main.cpp compress.cpp decompress.cpp \
    frequency_table.cpp huffman.cpp BIT_IO.cpp \
    -o compresso
```

---

## ▶️ Usage

### Compress a File

```bash
./compresso <input_file>
```

Example:

```bash
./compresso data.bin
```

Output:

```
data_compressed.bin
```

---

### Decompress a File

```bash
./compresso <compressed_file>
```

Example:

```bash
./compresso data_compressed.bin
```

Output:

```
data_decompressed.bin
```

---

## 🔍 Verification

To verify correctness after decompression:

```bash
sha256sum original_file decompressed_file
```

Matching hashes confirm **bit-for-bit correctness**.

---

## 🧪 Tested Scenarios

* Empty files
* Single-byte and single-symbol files
* Large binary files (7GB+)
* Text files
* Random binary data

---

## 🛠️ Concepts & Technologies Used

* Binary file I/O
* Bit-level encoding/decoding
* Huffman Coding
* Priority queues (min-heap)
* Tree traversal (DFS)
* Recursive algorithms
* Linux debugging and tooling (`gdb`, `objdump`, `sha256sum`)

---

## 📈 Future Improvements

* CLI flags (`-c`, `-d`)
* Multi-threaded compression
* Compression ratio benchmarking
* Support for additional algorithms (LZW, RLE)
* CRC / checksum validation
* Progress indicator for large files

---

## 👨‍💻 Author

Developed as a **systems-level C++ project** to explore real-world file compression, binary data handling, and low-level performance considerations.

---

## 📜 License

This project is released under the **MIT License**.
