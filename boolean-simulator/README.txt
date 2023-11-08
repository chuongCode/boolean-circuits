
File: README.txt
Creator: George Ferguson
Created: Mon Jul 16 15:19:39 2018
Time-stamp: <Tue Jul 17 15:19:21 EDT 2018 ferguson>


Simple Boolean circuit simulator written in C.

I had to replace my earlier reference-sharing implementation of circuit connections with an explicit list in order to support clean freeing of circuits and their components.

This code gets a clean report from valgrind when compiled with gcc on Fedora Linux (July 2017).

