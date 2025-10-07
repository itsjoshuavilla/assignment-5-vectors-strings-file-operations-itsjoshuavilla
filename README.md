[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/QhG80R_K)
# ECE_Assignment5
Working with Vectors, String functions, and File operations
# Lab Assignment 5
C++ program where we will use the string, vector, and fstream classes to read/write files and store data.

# Step 1
Create a struct in a header file called pixel.h with the following struct
```
struct _pixel
{
  float r;
  float g;
  float b;
  int x;
  int y;
};
typedef struct _pixel Pixel;
```
The values r,g,b contain 0.0 to 1.0 values to map into RGB color space.  The values x, y indicate the x and y pixel location on the screen.

# Step 2
Create a vector called pixel_list and defined like
```
std::vector<Pixel> pixel_list;
```
which will store every pixel read in the from the file.

# Step 3
Take a string from the command line for the file to read.  The file for input is called pixels.dat and located in this repository.  The format for this file is given as
```
0,0,0.4395700779928904,0.9343941844026555,0.11956329425119616
0,1,0.8524808236654031,0.8812383901083097,0.22561409174532054
0,2,0.2554656078947496,0.6427251273450297,0.7846795291785428
0,3,0.8167976025632453,0.8285117476156731,0.7443373845648841
```
where each value is comma separated.  The first value is the x location, the second value is the y location, third is r value, fourth the g value, and last is the b value.  The x-length for this data is 512 and the y-length is 256.  In total, there are 131072 pixels to be read in.  You will need to convert the strings to floats and integers.

Use a combination of string functions to parse each line and load each pixel into a Pixel object.  Think about using .find() and .substr() functions to extract values between commas.  Use a piece of paper to write out the index for of each string, and how a loop for .find() and .substr() would work.  Store each pixel object into the pixel_list vector using .push_back()

# Step 4
After reading in the data, make 2 functions.  The first function will calculate the average of the r,g,b values in the domain individually.  That is, average all r colors and give a result, all g colors and give a result, and all b colors and give a result.
The definition for this function is
```
void average_colors(std::vector<Pixel> &pixel_list);
```

Make a second function that flips all pixels vertically.  For example, in the y-direction, pixel 600 should become pixel 0 and pixel 0 should become pixel 600.  No modification in the x-direction. The function definition is
```
void flip_vertically(std::vector<Pixel> &pixel_list);
```

# Step 5
After flipping the image, save the new pixel list to a file called flipped.dat.  Output the individual x, y, r, g, b values in the same format as the input file.

# Grading Scale
Push your main.cpp, pixel.h, and flipped.dat file to the repository.
- 40% read in from file correctly
- 20% two functions created that operate properly
- 20% output of data to a file called flipped.dat
- 20% code produces expected output
