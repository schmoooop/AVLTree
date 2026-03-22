# AVL Tree in C++

This project implements an AVL tree in C++ using separate header and source files, along with unit tests and CMake for building.

## Features
- Self-balancing binary search tree
- AVL rotations to maintain balance
- Modular C++ project structure
- Unit testing with Catch2
- Build configuration with CMake

## Project Structure
- `src/AVLTree.h` — AVL tree declarations
- `src/AVLTree.cpp` — AVL tree implementation
- `src/main.cpp` — example driver
- `test-unit/test.cpp` — unit tests
- `CMakeLists.txt` — build configuration

## Build and Run

```bash
mkdir build
cd build
cmake ..
make
./AVLTree