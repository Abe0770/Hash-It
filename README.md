# Hash It

A simple C++ command-line utility for computing hashes of strings or files. Designed for ease of use and extensibility.

## Features

- Compute cryptographic hashes of **strings** and **files**
- Modular structure: easy to plug in new algorithms
- Open to contributions

## Available Hashes
<table>
  <tr>
    <th>Algorithm</th>
    <th>Flag</th>
    <th>Status</th>
  </tr>
  <tr>
    <td>SHA-256</td>
    <td>--SHA256</td>
    <td>Supported</td>
  </tr>
  <tr>
    <td>SHA-1</td>
    <td>--SHA1</td>
    <td>Planned</td>
  </tr>
  <tr>
    <td>SHA-512</td>
    <td>--SHA512</td>
    <td>Planned</td>
  </tr>
</table>

## Build Instructions

Make sure you have a C++17 compatible compiler installed (like `g++`), then run:

```bash
make
```

This will compile the project and generate an executable named `hash`.

## Usage

### Hash a string:

```bash
./getHash --SHA256 "hello world"
```

> No need for quotes if you use a single-word string. Use quotes for multi-word input.

### Hash a file:

```bash
./getHash --SHA256 --FILE /path/to/your/file.txt
```

The hash will be printed to the terminal.

## Contributing

Feel free to contribute by adding new hash algorithms (like SHA1, MD5, etc.).

- Fork this repo
- Create a new branch
- Add your changes
- Submit a pull request

We’ll be happy to review your contribution!

## License

This project is released under the MIT License.
