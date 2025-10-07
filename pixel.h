#ifndef PIXEL_H
#define PIXEL_H

// I'm defining a simple struct to hold one pixel.
// r,g,b are floats in [0.0, 1.0]; x,y are integer positions on the grid.
struct _pixel
{
    float r; // red   (0.0 -> 1.0)
    float g; // green (0.0 -> 1.0)
    float b; // blue  (0.0 -> 1.0)
    int x;   // x-coordinate (column)
    int y;   // y-coordinate (row)
};

// The assignment wants this typedef name exactly.
typedef struct _pixel Pixel;

#endif // PIXEL_H
