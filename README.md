# Overview
This is an implementation of a CSV parser that is written in C and CPP
using primarily standard library functions

The schema for this csv file is that you specify the type of data as the first line and then have
everythig else as just rows of data. This allows cross platform support

# TODO:
- Make casts to 32 bit and 64 bit data types for cross-platform support
- add support to automatically detect type?
- Memory Map reading and writing to files to support larger files
- default to given schema as well
- Investigate why it segfaults on files >2MB
