#include <stdio.h>
#include <string.h> //for memset function
#include <stdlib.h> //for fgets, sscanf, malloc...
#include <math.h> //for absolute value in the plotting lines function
#include "define.h"
#include "stack.h"

void initial_condition(machine* mac){                   //initial condition of the machine
    mac -> current.x = mac -> current.y = 0;            //set current position to (0,0);
    mac -> marked.x = mac -> marked.y = 0;              //set current position to (0,0);
    mac -> direction = East;                            //set the direction is East;
    mac -> num_colors = 0;                              //set the number of colors to 0
    memset(mac->colors, 0, sizeof(color)*(mac->num_colors));  //just to make sure it satisfies the initial condition which the bucket of color is empty, so I set it to 0
    mac -> num_opacities = 0;                           //the buckets of colors and opacity are both empty;
    memset(mac->opacities, 0, sizeof(opacity)*(mac->num_opacities)); //just to make sure it satisfies the initial condition which the bucket of opacity is empty, so I set it to 0
    mac -> num_layers = 1;                              //the stack contains a single layer;
    memset(mac -> layers[0].pixel, 0, sizeof(layer));   //set each pixel of this layer is made up of color (0,0,0) and opacity 0
}

//Pixel calculation
pixel get_current_pixel(machine *mac){
    int total_r, total_g, total_b, total_o;             //total of each color and the opacity
    int avg_r, avg_g, avg_b;                            //average of each color
    total_r = total_g = total_b = total_o = 0;
    avg_r = avg_g = avg_b = 0;
    pixel p;                       //variable pixel (current pixel) to return all the values we need such as each color and opacity
    //calculate the average of each color
    for (int i = 0; i < (mac -> num_colors); i++){      //loop from index 0th to (number_of_colors-th - 1) to get the total number of each color
        total_r += mac -> colors[i].r;
        total_g += mac -> colors[i].g;
        total_b += mac -> colors[i].b;
    }
    //find average of the color;
    avg_r = (mac -> num_colors == 0) ? 0 : total_r / mac -> num_colors; //avoid number/0;
    avg_g = (mac -> num_colors == 0) ? 0 : total_g / mac -> num_colors; //if the number of colors is 0 then avg of each color is automatically 0 as well
    avg_b = (mac -> num_colors == 0) ? 0 : total_b / mac -> num_colors;
    //calculate the average of opacity
    for (int i = 0; i < (mac -> num_opacities); i++){   //it loops the same way as color did above
        total_o += mac -> opacities[i].o; 
    }
    //check if this bucket is empty, 255 is taken as a value for the current opacity;
    if (mac -> num_opacities == 0){ 
        p.opacity.o = 255;
    }else{
        p.opacity.o = total_o / mac -> num_opacities; //average of the opacity is the current opacity
    }
    //find the colors of the current pixel
    //If the bucket of colors is empty, we take as a value 0 for each of the components of the current color
    if (mac -> num_colors == 0){
        p.color.r = p.color.g = p.color.b = 0;
    }else{
        p.color.r = (avg_r * p.opacity.o) / 255;
        p.color.g = (avg_g * p.opacity.o) / 255;
        p.color.b = (avg_b * p.opacity.o) / 255;
    }
    return p;
}

// ===== TO CHANGE CONDITION WHEN MEETS CERTAIN CHARACTER =====

void add_color(machine *mac, color c){          //we need this function to change condition when we meet certain character in the input file
    mac -> colors[mac -> num_colors] = c;       //add the color from the parameter to the bucket
    mac -> num_colors += 1;                     //plus 1 to the number of colors in the bucket
}

void add_opacity(machine *mac, opacity o){      //same with change color
  mac -> opacities[mac -> num_opacities] = o;   //add the opacity from the parameter to the bucket
  mac -> num_opacities += 1;                    //plus 1 to the number of opacties in the bucket
}

void add_layer(machine *mac, int w, int h){     //we need this for case c = 's'
  if (mac -> num_layers >= 10) return;
  layer* l = malloc(sizeof(layer));
  for (int i = 0; i < w; i++){
    for (int j = 0; j < h; j++){
        l->pixel[i][j].color.r = 0;
        l->pixel[i][j].color.g = 0;
        l->pixel[i][j].color.b = 0;
        l->pixel[i][j].opacity.o = 0;
    }
  }
  mac -> layers[mac -> num_layers] = *l;        //logically we should increment the number of layer first before assigning new layer to value 0(pixel), but in fact the stack of layers starts from index 0 
  mac -> num_layers += 1;
  free(l);
  l = NULL; //just to be safe
}

void move_cursor(machine *mac, int width, int height){
    int x = mac -> current.x;
    int y = mac -> current.y;
    //move the current by one step, but there are 4 directions so we have to increment the current for each position
    if (mac -> direction == West && x >= 0) x--; //if x = 0 then it goes to the other side of the screen, if not it moves left by 1 step
    if (mac -> direction == East && x <= width - 1) x++;
    if (mac -> direction == North && y >= 0) y--; //y-- because y-axis of the image screen is flipped from cartesian so to the top is negative
    if (mac -> direction == South && y <= height - 1) y++;
    //if the edge of the image has reached, we go to the other side else with return the poisition after we moved
    if(x < 0) x = width - 1; //because x,y axis in the screen starts from position 0 to width-1
    if(y < 0) y = height - 1;
    if(x >= width) x = 0;
    if(y >= height) y = 0;
    mac -> current.x = x;
    mac -> current.y = y;
}

void turn_clockwise(machine* mac){  //turn right 
  direction dir = mac -> direction;
  if (dir == North)  dir = East;
  else if (dir == East) dir = South;
  else if (dir == South) dir = West;
  else if (dir == West) dir = North;
  mac -> direction = dir;
}

void turn_counterclockwise(machine* mac){  //turn left
  direction dir = mac -> direction;
  if (dir == North) dir = West;
  else if (dir == West) dir = South;
  else if (dir == South) dir = East;
  else if (dir == East) dir = North;
  mac -> direction = dir;
}

//need this for function plotting_lines
void change_pixel(machine* mac, int x, int y){ //replace pixel at position x,y by current pixel
    pixel current = get_current_pixel(mac);
    mac -> layers[mac->num_layers-1].pixel[x][y].color.r = current.color.r;
    mac -> layers[mac->num_layers-1].pixel[x][y].color.g = current.color.g;
    mac -> layers[mac->num_layers-1].pixel[x][y].color.b = current.color.b;
    mac -> layers[mac->num_layers-1].pixel[x][y].opacity.o = current.opacity.o;
}

void plotting_lines(machine *mac, int x0, int y0, int x1, int y1){
    int d, s;
    int dx = x1 - x0;
    int dy = y1 - y0;
    if (abs(dx) > abs(dy)){
        d = abs(dx);
    }else{
        d = abs(dy);
    }
    if ((dx != 0 && dy != 0) && ((dx > 0 && dy > 0) || (dx < 0 && dy < 0))){
        s = 0;
    }else{
        s = 1;
    }
    int x = x0 * d + (d - s) / 2;
    int y = y0 * d + (d - s) / 2;
    if (d > 0){                             //repeat d times, so if d < 0 there is no 'times' to be repeated, but in fact (d is absolute value) just being cautious here because first I use while loop to decrement d 
        for (int i = 0; i < d; i++){
            change_pixel(mac, x/d, y/d);    //replace pixel at (x/d, y/d) by current pixel
            x = x + dx;
            y = y + dy; 
        }   
    }
    change_pixel(mac, x1, y1);              //replace pixel at (x1, y1) by current pixel
}

void fill_loop(int x, int y, pixel old, pixel new, layer* l, int size){
    if (l->pixel[x][y].color.r == new.color.r &&       //if the components are the same, we do nothing 
        l->pixel[x][y].color.g == new.color.g && 
        l->pixel[x][y].color.b == new.color.b && 
        l->pixel[x][y].opacity.o == new.opacity.o) return;

    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {-1, 0, 1, 0};

    stack st_x = NULL;
    stack st_y = NULL;

    push(x, &st_x);
    push(y, &st_y);

    while (st_x != NULL) {
        x = pop(&st_x);
        y = pop(&st_y);

        l->pixel[x][y].color.r = new.color.r;
        l->pixel[x][y].color.g = new.color.g;
        l->pixel[x][y].color.b = new.color.b;
        l->pixel[x][y].opacity.o = new.opacity.o;

        for (int i=0; i<4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < size && ny >= 0 && ny < size &&
                l->pixel[nx][ny].color.r == old.color.r &&
                l->pixel[nx][ny].color.g == old.color.g &&
                l->pixel[nx][ny].color.b == old.color.b &&
                l->pixel[nx][ny].opacity.o == old.opacity.o) {

                    push(nx, &st_x);
                    push(ny, &st_y);
            }
        }
    }
}

void fusion(layer* c1, layer* c0, int w, int h){ //initially it was c0, c1, but the output wasn't right then I made an inversion from c0 to c1 and vice versa (in the arguments and the variable store the calculation)
    layer* tmp;
    tmp = malloc(sizeof(layer));
    //store value of pixel(r,g,b,o) at each position into layer tmp created above (for below if condition)
    for (int i = 0; i < w; i++){
        for (int j = 0; j < h; j++){
            tmp->pixel[i][j].color.r = c1->pixel[i][j].color.r;
            tmp->pixel[i][j].color.g = c1->pixel[i][j].color.g;
            tmp->pixel[i][j].color.b = c1->pixel[i][j].color.b;
            tmp->pixel[i][j].opacity.o = c1->pixel[i][j].opacity.o;
        }
    }                                      
    for (int i = 0; i < w; i++){                 
        for (int j = 0; j < h; j++){
            c1->pixel[i][j].color.r = c0->pixel[i][j].color.r + (c1->pixel[i][j].color.r * (255 - c0->pixel[i][j].opacity.o) / 255);
            c1->pixel[i][j].color.g = c0->pixel[i][j].color.g + (c1->pixel[i][j].color.g * (255 - c0->pixel[i][j].opacity.o) / 255);
            c1->pixel[i][j].color.b = c0->pixel[i][j].color.b + (c1->pixel[i][j].color.b * (255 - c0->pixel[i][j].opacity.o) / 255);
            c1->pixel[i][j].opacity.o = c0->pixel[i][j].opacity.o + (c1->pixel[i][j].opacity.o * (255 - c0->pixel[i][j].opacity.o) / 255);
            //check if the color components are greater than opacity because in the remarque: the color components cannot be larger than the opacity component
            if((c1->pixel[i][j].color.r > c1->pixel[i][j].opacity.o && 
                c1->pixel[i][j].color.g > c1->pixel[i][j].opacity.o && 
                c1->pixel[i][j].color.b > c1->pixel[i][j].opacity.o)){
                        c1->pixel[i][j].color.r = tmp->pixel[i][j].color.r;
                        c1->pixel[i][j].color.g = tmp->pixel[i][j].color.g;
                        c1->pixel[i][j].color.b = tmp->pixel[i][j].color.b;
                        c1->pixel[i][j].opacity.o = tmp->pixel[i][j].opacity.o;
            }
        }
    }
    free(tmp);
    tmp = NULL; //just to be safe
}

void cutting_layers(layer* c1, layer* c0, int w, int h){
    for (int i = 0; i < w; i++){
        for (int j = 0; j < h; j++){
            c1->pixel[i][j].color.r = (c1->pixel[i][j].color.r * c0->pixel[i][j].opacity.o) / 255;
            c1->pixel[i][j].color.g = (c1->pixel[i][j].color.g * c0->pixel[i][j].opacity.o) / 255;
            c1->pixel[i][j].color.b = (c1->pixel[i][j].color.b * c0->pixel[i][j].opacity.o) / 255;
            c1->pixel[i][j].opacity.o = (c1->pixel[i][j].opacity.o * c0->pixel[i][j].opacity.o) / 255;
        }
    }  
}

// ==== TO WRITE THE FINAL OUTPUT IN PPM FORMAT ====

void write_ppm(machine* mac, FILE* img, int w, int h){
    // Use the img parameter as the file pointer
    img = fopen("richard_img.ppm", "w");  //create an image in write format to write pixel into the created ppm file 
    // header of PPM format
    fprintf(img, "P3\n");                 //P6 is binary type (P3 is text mode)
    fprintf(img, "%d %d\n", w, h);        //width and height
    fprintf(img, "255\n");                //maximum of each component

    layer *res = malloc(sizeof(layer));   //allocate memory for the topmost layer so that we can get access its pixel, and free it later on
    *res = mac->layers[mac->num_layers - 1];

    for (int i = 0; i < w; i++) {         //loop for each position until the size of the image, basically write the whole image
        for (int j = 0; j < h; j++) {
        pixel *p = malloc(sizeof(pixel));
        *p = res->pixel[j][i];            //j,i because previously when I display i,j it displays the mirror image of the original
        fprintf(img, "%d %d %d ", p->color.r, p->color.g, p->color.b); // write the pixel(RGB) values to the file img
        } 
    }
    free(res);
    res = NULL; //just to be safe
    fclose(img);
}