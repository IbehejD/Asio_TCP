# Asio TCP Playground

This project is a small playground for experimenting with Boost.Asio-style asynchronous networking using standalone Asio.

It is designed to compare different approaches to handling asynchronous work, from classic callback-based code to newer coroutine-based flows. The goal is to make it easy to explore how the same TCP client/server idea can be implemented with different async styles and levels of abstraction.

## What this project uses

- Standalone Asio instead of the full Boost distribution
- Modern C++23
- Separate client and server executables

## Building

The repository is set up to build with CMake and Conan.

### Recommended build script

```bash
./build.sh
```

This script removes the existing build directory, installs dependencies through Conan, configures CMake with the `conan-debug` preset, and builds the project.

### Manual build steps

```bash
conan install .conan --output-folder=build --build=missing -pr:h=.conan/profiles/default -pr:b=.conan/profiles/default -s build_type=Debug
cmake --preset conan-debug
cmake --build --preset conan-debug
```

## Targets

- `client_app`
- `server_app`

## Purpose

The code in this repository is meant for learning and experimentation. It focuses on TCP communication patterns and different ways to structure asynchronous handling, rather than providing a production-ready networking framework.
