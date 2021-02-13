## Contributing

- i686-w64-mingw32-gcc - C/C++ compiler
- Vim @ WSL - IDE

To compile the project, run `make build`.  
To compile the project with Docker, run `make docker_build`.

Each function should be ported in a separate commit. After porting each
function, you should update the progress map by editing the `docs/progress.txt`
file and executing `make docs`.

This project uses `clang-format` to take care of automatic code formatting. To
ensure your code conforms to the standard, please run `make lint` after each
commit.