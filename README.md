# Hash It

A simple C++ command-line utility for computing SHA256 hashes of strings or files. Designed for ease of use and extensibility.

## Features

- Compute SHA256 hash of a **string**
- Compute SHA256 hash of a **file**
- Lightweight and modular code
- Easy to contribute (add new algorithms via pull request)

## 🛠️ Build Instructions

Make sure you have a C++17 compatible compiler installed (like `g++`), then run:

```bash
make
```

This will compile the project and generate an executable named `hash`.

## 🧪 Usage

### Hash a string:

```bash
./hash --SHA256 --STRING "hello world"
```

> 💡 No need for quotes if you use a single-word string. Use quotes for multi-word input.

### Hash a file:

```bash
./hash --SHA256 --FILE /path/to/your/file.txt
```

The hash will be printed to the terminal.

## 🙌 Contributing

Feel free to contribute by adding new hash algorithms (like SHA1, MD5, etc.).

- Fork this repo
- Create a new branch
- Add your changes
- Submit a pull request

We’ll be happy to review your contribution!

## 📄 License

This project is released under the MIT License.
