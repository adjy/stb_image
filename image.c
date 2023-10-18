#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct Pixel{
    int8_t R, G, B;
};

struct Image{
    struct Pixel *img;
    int w;
    int h;
};

struct Complexe{
    float re, im;
};

struct Complexe c_add(struct Complexe c1, struct Complexe c2){
    struct Complexe c;
    c.re = c1.re + c2.re;
    c.im = c1.im + c2.im;
    return c;
}

struct Complexe c_mult(struct Complexe c1, struct Complexe c2){
    struct Complexe c;
    c.re = (c1.re * c2.re) - (c1.im * c2.im);
    c.im = (c1.re * c2.im) + (c1.im * c2.re);

    return c;
}

float clacul(struct Complexe c){
    struct Complexe z = {0,0};
    for(int i=0; i< 100; i++){
        struct Complexe z1 =  c_add(c_mult(z, z) , c ); 
        z = z1;

        if(sqrt(z.re * z.re + z.im * z.im) > 2)
            return 0;
    }
    return 1;
}

struct Image createImg(int width, int height){
    struct Image image;
    image.w = width;
    image.h = height;

    image.img = malloc((width * height) * 3 * sizeof(int8_t));

    // struct Pixel degrad = {100, 100, 100};

     for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            float x = (float) i / (float )width - 0.5;
            float y = (float) j / (float) height - 0.5;

            struct Complexe c = {x,y};
            // c = c_mult(c,c);
            
             x = c.re;
             y = c.im;

            int8_t val = sqrt(x*x + y*y) / 10;

            val = clacul(c) * 255;
            // printf("%d", val);

            // val = cos(10 *i) * sin (20 * j) * 125;

            image.img[i * height + j ].R = val  ;
            image.img[i * height + j  ].G = val + (i * height + j) + 100 ;
            image.img[i * height + j  ].B =val + (i * height + j) + 150;
        }
    }
    return image;
}


void write_img(){

    const int width = 100;
    const int height = 100;
    const int channel = 3;

    int8_t* pixels = malloc(width * height * channel * sizeof(int8_t));

    int8_t index = 0;
    for (int i = 0; i < width*height*channel; i=i+3){
                int8_t r = 255;
                int8_t g = 255;
                int8_t b = 255;

                pixels[i+0] = r;
                pixels[i+1] = g;
                pixels[i+2] = b;
        }

    stbi_write_jpg("stbpng.jpg", width, height, channel, pixels, 1);

}

void write_img1t(){
    const int width = 100;
    const int height = 100;
    const int channel = 1;
    
    int8_t image[width * height]; 
    for(int i = 0; i <width * height; i++)
        image[i] = 255;

    stbi_write_jpg("test22.png", width, height, channel, image, 1);
}


int main(int argc, char* argv[]){



    // comp = type image ( RGB, RGBA)
    //data = mon image en 1 D
     // stride_in_bytes: w * type_of type de donner dans l'image

    // int h = 5;
    // int w = 5;

   
    int width = 2000;
    int height = 2000;

    struct Image img = createImg (width, height);
    stbi_write_jpg("image.jpg", width, height, 3, img.img, 0);
    
    // write_img1t();

}


// gcc image.c -o main -lm