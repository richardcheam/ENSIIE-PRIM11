#include <stdio.h> 
#include <stdlib.h> //for malloc
#include <string.h> //for memset and strcat
#include "function.h"
#include <SDL2/SDL.h> //for the last bonus question (GUI)

//The primary difference between the getchar() and getc() is that the getc() is capable of reading from any input scheme, 
//while the getchar() is capable of reading from the standard input. Hence, getchar() becomes equivalent to the getc(stdin).
//(c = getchar()) != EOF)

int main(int argc, char* argv[]){
  //The proposed PPM format consists of a first line, which contains a given integer in text mode. This integer corresponds to the width and height of the image that will be produced.
  //so I initialize two integers to read first line of the input
  int width, height;
  width = height = 0; //avoid warning from -Wall
  machine *mac = malloc(sizeof(machine)); //allocate memo for machine

  layer *l; //for fusion,cut,fill(acts as c1 for fusion and cutting)
  pixel old, new; //for fill function
  layer *c0; //for 
  
  char c;
  char buf[256];
  
  if (argc == 1){ //for when the first argument is not provided, so we can use redirect sign to read the file (ex: ./prog < test.ipi)
      //img = fopen(argv[1], "r"); //open read file using argv[]
      fgets(buf, sizeof(buf), stdin); //read the line from standard input 
      sscanf(buf, "%d %d", &width, &height);
      height = width; //assign width to height to be a sqaure image, hence it is equivalent to one another
      initial_condition(mac); //initialial condition of the machine
      
      //GUI
      if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return -1;
      };
      SDL_Window *win = SDL_CreateWindow("WIN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
      SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
      SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(ren);

      //we have to assign l,c0 into while loop because each time we add layer, fill, fusion, cut, as l,c0 change we have to keep track in the while loop, otherwise it will be segmentation fault  
      while ((c = getchar()) != EOF){ //use getchar to the get the character inputed by the user, hence it equally becomes getc(stdin)
        l = &(mac -> layers[mac->num_layers-1]); // topmost layer //for fusion,cutting,fill (a pointer points to the topmost layer)
        c0 = &(mac -> layers[mac->num_layers-2]); //under the topmost layer here num->layers[num_layers-2] is topmost because we add a new layer before starting (a pointer points to the layer which is just below the topmost layer)
        if (c == 'n') add_color(mac, (color){0, 0, 0}); //same with color.r = 0, color.g = 0, color.b = 0;
        if (c == 'r') add_color(mac, (color){255, 0, 0});
        if (c == 'g') add_color(mac, (color){0, 255, 0});
        if (c == 'b') add_color(mac, (color){0, 0, 255});
        if (c == 'y') add_color(mac, (color){255, 255, 0});
        if (c == 'm') add_color(mac, (color){255, 0, 255});
        if (c == 'c') add_color(mac, (color){0, 255, 255});
        if (c == 'w') add_color(mac, (color){255, 255, 255});
        if (c == 't') add_opacity(mac, (opacity){0});
        if (c == 'o') add_opacity(mac, (opacity){255});
        if (c == 'i'){
          mac -> num_colors = 0;
          memset(mac->colors, 0, sizeof(mac->colors));
          mac -> num_opacities = 0;
          memset(mac->opacities, 0, sizeof(mac->opacities));
        }
        if (c == 'v') move_cursor(mac, width, height);
        if (c == 'h') turn_clockwise(mac);
        if (c == 'a') turn_counterclockwise(mac);
        if (c == 'p'){
          mac -> marked.x = mac -> current.x;
          mac -> marked.y = mac -> current.y;
        }
        if (c == 'l') plotting_lines(mac, mac->current.x, mac->current.y, mac->marked.x, mac->marked.y);
        if (c == 'f') { 
            old = l->pixel[mac->current.x][mac->current.y];
            new = get_current_pixel(mac);
            fill_loop(mac->current.x, mac->current.y, old, new, l, width);
        }
        if (c == 's') add_layer(mac, width, height);
        if (c == 'e'){
          if (mac -> num_layers > 1){
              fusion(c0, l, width, height);
              mac -> num_layers -= 1;
          }
        }
        if (c == 'j'){
            if (mac -> num_layers > 1){
              cutting_layers(c0, l, width, height);
              mac -> num_layers -= 1;
          }
        }
        //GUI
        if (c == 'l' || c == 'f' || c == 'e' || c == 'j'){ //only this 4 conditions as they are essential for user to see how the image is constructed, espcially l(plotting lines), and f(fill color)
            layer *res = malloc(sizeof(layer));
            *res = mac->layers[mac->num_layers - 1];
            SDL_PumpEvents();
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    pixel *p = malloc(sizeof(pixel));
                    *p = res->pixel[j][i]; 

                    
                    SDL_SetRenderDrawColor(ren, p->color.r, p->color.g, p->color.b, p->opacity.o);
                    SDL_RenderDrawPoint(ren, j, i);

                    free(p);
                }
            }
            SDL_RenderPresent(ren);
            free(res);
        }
      }

      FILE* my_img = NULL; //create new file to write ppm (initialize it to NULL in order to escape warning from -Wall)
      write_ppm(mac, my_img, width, height);

      int is_running = 1; //after while loop  
      SDL_Event event;    //running the window is closed
      while (is_running) {
          while (SDL_PollEvent(&event)) {
              if (event.type == SDL_QUIT) {
                  is_running = 0;
              }
          }
      }
      SDL_Quit();
  }

  if (argc == 2){ //handle the bonus question for when the first argument provided
      FILE* img = fopen(argv[1], "r"); //open read file using argv[]
      fgets(buf, sizeof(buf), img); 
      sscanf(buf, "%d %d", &width, &height);
      height = width; //assign width to height to be a sqaure image
      initial_condition(mac); //initialial condition of the machine

      //GUI
      if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return -1;
      };
      SDL_Window *win = SDL_CreateWindow("WIN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
      SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
      SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(ren);


      //we have to assign l,c0 into while loop because each time we add layer, fill, fusion, cut, as l,c0 change we have to keep track in the while loop, otherwise it will be segmentation fault  
      while ((c = getc(img)) != EOF){ //use getchar to the get the character inputed by the user
        l = &(mac -> layers[mac->num_layers-1]); // topmost layer //for fusion,cutting,fill
        c0 = &(mac -> layers[mac->num_layers-2]); //under the topmost layer here num->layers[num_layers-2] is topmost because we add a new layer before starting
        if (c == 'n') add_color(mac, (color){0, 0, 0}); //same with color.r = 0, color.g = 0, color.b = 0;
        if (c == 'r') add_color(mac, (color){255, 0, 0});
        if (c == 'g') add_color(mac, (color){0, 255, 0});
        if (c == 'b') add_color(mac, (color){0, 0, 255});
        if (c == 'y') add_color(mac, (color){255, 255, 0});
        if (c == 'm') add_color(mac, (color){255, 0, 255});
        if (c == 'c') add_color(mac, (color){0, 255, 255});
        if (c == 'w') add_color(mac, (color){255, 255, 255});
        if (c == 't') add_opacity(mac, (opacity){0});
        if (c == 'o') add_opacity(mac, (opacity){255});
        if (c == 'i'){
          mac -> num_colors = 0;
          memset(mac->colors, 0, sizeof(mac->colors));
          mac -> num_opacities = 0;
          memset(mac->opacities, 0, sizeof(mac->opacities));
        }
        if (c == 'v') move_cursor(mac, width, height);
        if (c == 'h') turn_clockwise(mac);
        if (c == 'a') turn_counterclockwise(mac);
        if (c == 'p'){
          mac -> marked.x = mac -> current.x;
          mac -> marked.y = mac -> current.y;
        }
        if (c == 'l') plotting_lines(mac, mac->current.x, mac->current.y, mac->marked.x, mac->marked.y);
        if (c == 'f') { 
            old = l->pixel[mac->current.x][mac->current.y];
            new = get_current_pixel(mac);
            fill_loop(mac->current.x, mac->current.y, old, new, l, height);
        }
        if (c == 's') add_layer(mac, width, height);
        if (c == 'e'){
          if (mac -> num_layers > 1){
              fusion(c0, l, width, height);
              mac -> num_layers -= 1;
          }
        }
        if (c == 'j'){
            if (mac -> num_layers != 1){
              cutting_layers(c0, l, width, height);
              mac -> num_layers -= 1;
          }
        }
        //GUI
        if (c == 'l' || c == 'f' || c == 'e' || c == 'j'){ //only this 4 conditions as they are essential for user to see how the image is constructed, espcially l(plotting lines), and f(fill color)
            layer *res = malloc(sizeof(layer));
            *res = mac->layers[mac->num_layers - 1];
            SDL_PumpEvents();
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    pixel *p = malloc(sizeof(pixel));
                    *p = res->pixel[j][i]; 
              
                    SDL_SetRenderDrawColor(ren, p->color.r, p->color.g, p->color.b, p->opacity.o);
                    SDL_RenderDrawPoint(ren, j, i);

                    free(p);
                }
            }
            SDL_RenderPresent(ren);
            free(res);
        }
      }
      fclose(img); //close the input file after finished reading it
      FILE* my_img = NULL; //create new file to write ppm (initialize it to NULL in order to escape warning from -Wall)
      write_ppm(mac, my_img, width, height);

      int is_running = 1; //after while loop
      SDL_Event event;    //running the window is closed
      while (is_running) {
          while (SDL_PollEvent(&event)) {
              if (event.type == SDL_QUIT) {
                  is_running = 0;
              }
          }
      }
      SDL_Quit();
  }

  if (argc == 3){ //handle the bonus question if a second argument is provided
      char* name = argv[2];
      char extension[] = ".ppm";
      FILE* img = fopen(argv[1], "r"); //open read file using argv[]
      fgets(buf, sizeof(buf), img); 
      sscanf(buf, "%d %d", &width, &height);
      height = width; //assign width to height to be a sqaure image
      initial_condition(mac); //initialial condition of the machine

      //GUI
      if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return -1;
      };
      SDL_Window *win = SDL_CreateWindow("WIN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
      SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
      SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(ren);
      
      //we have to assign l,c0 into while loop because each time we add layer, fill, fusion, cut, as l,c0 change we have to keep track in the while loop, otherwise it will be segmentation fault  
      while ((c = getc(img)) != EOF){ //use getchar to the get the character inputed by the user
        l = &(mac -> layers[mac->num_layers-1]); // topmost layer //for fusion,cutting,fill
        c0 = &(mac -> layers[mac->num_layers-2]); //under the topmost layer here num->layers[num_layers-2] is topmost because we add a new layer before starting
        if (c == 'n') add_color(mac, (color){0, 0, 0}); //same with color.r = 0, color.g = 0, color.b = 0;
        if (c == 'r') add_color(mac, (color){255, 0, 0});
        if (c == 'g') add_color(mac, (color){0, 255, 0});
        if (c == 'b') add_color(mac, (color){0, 0, 255});
        if (c == 'y') add_color(mac, (color){255, 255, 0});
        if (c == 'm') add_color(mac, (color){255, 0, 255});
        if (c == 'c') add_color(mac, (color){0, 255, 255});
        if (c == 'w') add_color(mac, (color){255, 255, 255});
        if (c == 't') add_opacity(mac, (opacity){0});
        if (c == 'o') add_opacity(mac, (opacity){255});
        if (c == 'i'){
          mac -> num_colors = 0;
          memset(mac->colors, 0, sizeof(mac->colors));
          mac -> num_opacities = 0;
          memset(mac->opacities, 0, sizeof(mac->opacities));
        }
        if (c == 'v') move_cursor(mac, width, height);
        if (c == 'h') turn_clockwise(mac);
        if (c == 'a') turn_counterclockwise(mac);
        if (c == 'p'){
          mac -> marked.x = mac -> current.x;
          mac -> marked.y = mac -> current.y;
        }
        if (c == 'l') plotting_lines(mac, mac->current.x, mac->current.y, mac->marked.x, mac->marked.y);
        if (c == 'f') { 
            old = l->pixel[mac->current.x][mac->current.y];
            new = get_current_pixel(mac);
            fill_loop(mac->current.x, mac->current.y, old, new, l, height);
        }
        if (c == 's') add_layer(mac, width, height);
        if (c == 'e'){
          if (mac -> num_layers > 1){
              fusion(c0, l, width, height);
              mac -> num_layers -= 1;
          }
        }
        if (c == 'j'){
            if (mac -> num_layers > 1){
              cutting_layers(c0, l, width, height);
              mac -> num_layers -= 1;
          }
        }
        //GUI
        if (c == 'l' || c == 'f' || c == 'e' || c == 'j'){ //only this 4 conditions as they are essential for user to see how the image is constructed, espcially l(plotting lines), and f(fill color)
            layer *res = malloc(sizeof(layer));
            *res = mac->layers[mac->num_layers - 1];
            SDL_PumpEvents();
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    pixel *p = malloc(sizeof(pixel));
                    *p = res->pixel[j][i]; 
              
                    SDL_SetRenderDrawColor(ren, p->color.r, p->color.g, p->color.b, p->opacity.o);
                    SDL_RenderDrawPoint(ren, j, i);

                    free(p);
                }
            }
            SDL_RenderPresent(ren);
            free(res);
        }
      }

      //here using function write_ppm is a bit hard to proffer the name as the second argument, so I decided to do it manually in main for the condition argv[2] provided
      FILE* my_img = NULL;
      strcat(name, extension); //use the concatenation of string to add the extension ".ppm" into the name
      my_img = fopen(name, "w");  //create an image in write format to write pixel into the created ppm file 
      // header of PPM format
      fprintf(my_img, "P3\n");                 //P6 is binary type (P3 is text mode)
      fprintf(my_img, "%d %d\n", width, height);        //width and height
      fprintf(my_img, "255\n");                //maximum of each component

      layer *res = malloc(sizeof(layer));   //allocate memory for the topmost layer so that we can get access its pixel, and free it later on
      *res = mac->layers[mac->num_layers - 1];

      for (int i = 0; i < width; i++) {         //loop for each position until the size of the image, basically write the whole image
          for (int j = 0; j < height; j++) {
          pixel *p = malloc(sizeof(pixel));
          *p = res->pixel[j][i];            //j,i because previously when I display i,j it displays the mirror image of the original
          fprintf(my_img, "%d %d %d ", p->color.r, p->color.g, p->color.b); // write the pixel(RGB) values to the file my_img
          } 
      }
      fclose(img); //close the input file that we wished to read (argv[1])
      free(res);
      res = NULL; //just to be safe
      fclose(my_img);

      int is_running = 1; //after while loop
      SDL_Event event;    //running the window is closed
      while (is_running) {
          while (SDL_PollEvent(&event)) {
              if (event.type == SDL_QUIT) {
                  is_running = 0;
              }
          }
      }
      SDL_Quit();
  }

  if (argc > 3){ //handle the bonus question if the other arguments will be ignored, with a warning about the standard error output.
    fprintf(stderr, "!! Attention !! Three ways to use the machine are:\nUsage: ./prog < test.ipi OR\n       ./prog test.ipi   OR\n       ./prog test.ipi 'name_of_ouput_image'\n");
    exit(0);
  }

  free(mac); //free machine after allocation
  mac = NULL; //just to be safe
  return 0;
}