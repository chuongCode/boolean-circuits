Simple Boolean circuit simulator written in C.

I had to replace my earlier reference-sharing implementation of circuit connections with an explicit list in order to support clean freeing of circuits and their components.

This code gets a clean report from valgrind when compiled with gcc on Fedora Linux (November 2023).

