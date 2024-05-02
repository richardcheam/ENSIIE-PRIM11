#ifndef DEFINE_H //include guard
#define DEFINE_H

#define MAX_LAYERS 10 //because it counts from 0-9, hence there are 10 layers in total
#define MAX_COLORS 10000000 //assign value as big as possible because it was segmentation fault as the bucket of colors reaches its limit
#define MAX_OPACITIES 10000000 //same here with the opacity
#define MAX_WIDTH 1000 //first I gave it to 10000 then the GUI is taking too long to construct 
#define MAX_HEIGHT 1000 //first I gave it to 10000 then the GUI is taking too long to construct 

typedef struct {    //two integers indicating the position of the cursor; 
    int x, y;
} position;

typedef enum{       //an element that indicates the direction of the cursor; it can be North, East, South or West; enum here offers an easy way for comparison when needed 
    North, East, South, West    //automatically assigned value by the compiler (0, 1, 2, 3);
} direction; 

typedef struct {    //a multiset of colors that represents the bucket in which color doses are mixed to produce the current color;
    unsigned char r, g, b;      //unsigned char because its range is from 2ˆ8-1 which is 255 it goes back and start from to 0 if the digit is bigger than 255, and vice versa for negative number
} color;

typedef struct {    //a multiset of opacities that represents the bucket in which doses of opacities are mixed to produce the current opacity;
    unsigned char o;            //the same way with rgb above
} opacity;

typedef struct {    //a pixel consists of R G B and the opacity
    color color;
    opacity opacity;
} pixel;

typedef struct {
    pixel pixel[MAX_WIDTH][MAX_HEIGHT]; //a pointer to a variable whose datatype is pixel
} layer;            //a layer is a square grid of pixels, from the size of the image to be produced in the end.

typedef struct {
    position current, marked; 
    direction direction;
    color colors[MAX_COLORS];         //bucket of color
    int num_colors;                   //to keep track of the number of colors in the bucket
    opacity opacities[MAX_OPACITIES]; //bucket of opacity
    int num_opacities;                //to keep track of the number of opacities in the bucket
    layer layers[MAX_LAYERS + 1];     //stack of layers / max+1 because previously when I print the number of layers after adding more than 10 it starts over from 0, so here max+1 the num_layers stay the same after 10
    int num_layers;                   //to keep track the number of layers in the stack
} machine;

#endif