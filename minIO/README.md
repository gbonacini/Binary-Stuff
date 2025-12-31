Description:
============

* This mini library shows how to do I/O in C++ without using any part of standard library (no dependencies, no stdlib include file, no link);
* It requires Linux 64 bit, x86-64 platform;
* In order to do that, an inline assembly code wraps directly Linux sycalls;
* This library suports: read/write from/to terminal (stdin / stdout) or files, connection to tcp socket servers (tcp client) and some minimal utilities to handle strings, etc;
* See "examples" directory for demos and makefile example.

