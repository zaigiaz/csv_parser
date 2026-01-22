# Overview
This is an implementation of a CSV parser that is written in C and CPP
using primarily standard library functions

The schema for this csv file is that you specify the type of data as the first line and then have
everythig else as just rows of data. This allows cross platform support

# TODO:
- Add functionality to convert type of data to number or float, or char, etc.
- This is for computational purposes so the end user doesnt have to directly convert data themselves
- separate out reading a single line into a function for above functionality?
- Make casts to 32 bit and 64 bit data types for cross-platform support

# Example file
string,int,float,char
John,5,5.5,t
Isabella,124,1.994,f
Aaron,100,0.001,t
