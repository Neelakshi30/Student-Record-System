# Student Record System

A simple C program to manage student records (add, show, search, delete) using a binary file. This repository contains:

- main.c — the program source code
- Neelakshi.txt — (runtime data file created by the program)

## Building

- Linux/macOS: gcc main.c -o main
- Windows (MinGW/MSYS): gcc main.c -o main.exe

## Usage

Run the compiled executable and follow the menu prompts. The program stores records in a binary file named `Neelakshi.txt` in the current working directory.

## Notes

- The program uses ANSI color escape sequences; on Windows the program attempts to enable ANSI processing.
- Records are stored in binary format. Do not edit `Neelakshi.txt` with a text editor unless you convert formats.

## License

This project is licensed under the MIT License — see the LICENSE file for details.
