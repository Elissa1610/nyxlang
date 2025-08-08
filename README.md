# InsaneLang

InsaneLang is a next-generation systems programming language that aims to be C++ on steroids. It is designed to deliver ultra performance, safety, and expressiveness without the historical baggage of older systems languages.

## Vision

- **Performance**: Equal to or faster than C++ and Rust.
- **Safety**: No undefined behavior by default; memory safety is guaranteed unless you explicitly opt into unsafe blocks.
- **Power**: Direct access to hardware and the operating system is available when you need it.
- **Metaprogramming**: Built‑in reflection, macros, and compile‑time evaluation without template headaches.
- **Concurrency**: Native async/await and an actor model with zero‑cost abstractions.
- **Memory Models**: Choose stack, heap, GPU, or other memory regions with simple annotations.
- **Modules**: No header files or include hell; proper modules with explicit imports.
- **Inline Assembly**: Write inline assembly with type safety.
- **AI Optimizer**: An optional AI module can optimize your code during compilation for your specific target platform.
- **Testing & Debugging**: Unit testing, fuzzing, and symbolic execution are integrated into the language and compiler.

## Compiler Architecture

The InsaneLang compiler is built in a modular fashion using C++:

1. **Lexer** – Converts the raw source code into a sequence of tokens.
2. **Parser** – Transforms tokens into an Abstract Syntax Tree (AST).
3. **Semantic Analyzer** – Performs type checking and resolves identifiers.
4. **Code Generator** – Emits LLVM IR or native code.
5. **Optimizer** – Applies traditional optimizations and optional AI‑assisted passes.

The current code in this repository contains a simple skeleton for the lexer, parser, and a driver program. It serves as a starting point for building a full InsaneLang compiler.

## Building

You can build the skeleton compiler with CMake:

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

This will produce an `insanelang` executable.

## Using the Skeleton Compiler

The current compiler doesn't implement a full language yet. It tokenizes the input file and reports the number of tokens to demonstrate the basic infrastructure. You can run it like this:

```sh
./insanelang path/to/source.isn
```

## Contributing

This project is at an early stage. Contributions are welcome! Feel free to open issues or pull requests.
