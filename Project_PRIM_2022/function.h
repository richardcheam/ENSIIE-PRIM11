#ifndef FUNCTION_H //include guard
#define FUNCTION_H

#include "define.h"

/* @ requires mac points to a valid machine 
   @ assigns *mac
   @ ensures a successful initialization of the machine */
void initial_condition(machine *mac);

/* @ requires mac points to a valid machine 
   @ assigns *mac
   @ ensures the calculation of the current color which is the average of the colors contained in the bucket and return a pixel which consists of RGB and Opacity after the calculation */
pixel get_current_pixel(machine *mac);

/* @ requires mac points to a valid machine 
   @ assigns *mac
   @ ensures the addition of an input color into the bucket of colors, and the increment of number of total colors in the bucket */
void add_color(machine *mac, color c);

/* @ requires mac points to a valid machine 
   @ assigns *mac
   @ ensures the addition of an input opacity into the bucket of doses of opacity, and the increment of number of doses of opacity in the bucket */
void add_opacity(machine *mac, opacity o);

/* @ requires mac points to a valid machine 
   @ assigns a pointer l
   @ ensures an addition of a layer into machine with each pixel of this new layer will be made up of color (0,0,0) and opacity 0; if there are already 10 layers in the stack, it does nothing */
void add_layer(machine *mac, int w, int h);

/* @ requires mac points to a valid machine 
   @ assigns *mac
   @ ensures the movement of a cursor for case 'v' */
void move_cursor(machine *mac, int width, int height);

/* @ requires mac points to a valid machine 
   @ assigns *mac
   @ ensures the rotation of the direction of the machine in clockwise direction(right) */
void turn_clockwise(machine *mac);

/* @ requires mac points to a valid machine 
   @ assigns *mac
   @ ensures the rotation of the direction of the machine in clockwise direction(left)*/
void turn_counterclockwise(machine *mac);

/* @ requires mac points to a valid machine 
   @ assigns *mac
   @ ensures the change of pixel at coordinate (x,y) by replacing it with the pixel calculated using function get_current_pixel */
void change_pixel(machine *mac, int x, int y);

/* @ requires mac points to a valid machine 
   @ assigns *mac
   @ ensures the process of drawing/plotting a line between the cursor position(x0, y0) and the marked position(x1, y1) */
void plotting_lines(machine *mac, int x0, int y0, int x1, int y1);

/* @ requires mac, l point to a valid machine, layer respectively
   @ assigns *mac, old, new, *l
   @ ensures the filling on the area of the same color around the cursor by replacing it with the current color */
void fill_loop(int x, int y, pixel old, pixel new, layer* l, int size);

/* @ requires c0 and c1 point to a valid layer
   @ assigns *c0, *c1
   @ ensures the fusion or merging of two topmost layers, then remove one of the layer on top due to the fusion */
void fusion(layer *c0, layer *c1, int w, int h);

/* @ requires c0 and c1 point to a valid layer
   @ assigns *c0, *c1
   @ ensures the cutting of the layer below the topmost by using as a mask the opacities of the one at the top, then remove one layer on top */
void cutting_layers(layer *c0, layer *c1, int w, int h);

/* @ requires mac points to a valid machine, file pointer
   @ assigns *mac
   @ ensures the production of the final image in PPM format */
void write_ppm(machine *mac, FILE *img, int w, int h);

#endif