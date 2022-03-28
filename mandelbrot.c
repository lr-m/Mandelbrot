/*
A simple example of using the gfx library.
CSE 20211
9/7/2011
by Prof. Thain
*/

#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"
#include <math.h>
#include <time.h>

// Start and end of complex and imaginary planes
#define RE_START -2.5
#define RE_END 1.5
#define IM_START -1.5
#define IM_END 1.5

// Width and height of canvas
#define WIDTH 1920
#define HEIGHT 1080

// Struct for complex numbers
struct complex{
	double real;
	double imaginary;
} typedef Complex;

// Abs of complex number
double complex_abs(Complex* num1){
	return sqrt((num1->real * num1->real) + (num1->imaginary * num1->imaginary));
}

// Square the passed complex number
void comp_square(Complex* num1){
	double new_real = num1->real*num1->real - num1->imaginary*num1->imaginary;
	double new_imaginary = 2*num1->real*num1->imaginary;

	num1->real = new_real;
	num1->imaginary = new_imaginary;
}

// Add the second complex number to the first
void comp_add(Complex* num1, Complex* num2){
	num1->imaginary += num2->imaginary;
	num1->real += num2->real;
}

// Print passed complex number
void print_complex(Complex* c){
	printf("(%fi + %fj)\n", c->real, c->imaginary);
}

// Calculate iterations of mandelbrot
float mandelbrot(Complex* c, int iterations){
	Complex* z = malloc(sizeof(Complex));
	z->real = 0;
	z->imaginary = 0;

	int n = 0;

	while(complex_abs(z) < 2 && n < iterations){
		comp_square(z);
		comp_add(z, c);
		n++;
	}

	free(z);

	return n;
}

// Draws the mandelbrot screen with max iterations as passed
void draw_mandelbrot(int iterations){
	Complex* c = (Complex*) malloc(sizeof(Complex));
	for (double i = 0; i < WIDTH; i++){
		for (double j = 0; j < HEIGHT; j++){
			c -> real = RE_START + (i/WIDTH) * (RE_END - RE_START);
			c -> imaginary = IM_START + (j/HEIGHT) * (IM_END - IM_START);

			float mandel = mandelbrot(c, iterations);

			float f = mandel/iterations;

			float a = 4 - (1-f)/0.25;
			int X = floor(a);
			int Y = floor(255*(a-X));

			if (X == 0){
				gfx_color(255, Y, 0);
			} else if (X == 1) {
				gfx_color(255-Y, 255, 0);
			} else if (X == 2){
				gfx_color(0, 255, Y);
			} else if (X == 3){
				gfx_color(0, 255-Y, 255);
			} else if (X == 4){
				gfx_color(0, 0, 0);
			}

			gfx_point(i, j);
		}
	}
	free(c);
}

int main()
{
	char key;

	srand(time(NULL));

	// Open a new window for drawing.
	gfx_open(WIDTH, HEIGHT, "Mandelbrot");

	// Set the current drawing color to green.
	gfx_color(255,0,0);

	gfx_point(300, 300);

	// Draw a triangle on the screen.
	gfx_line(100,100,200,100);
	gfx_line(200,100,150,150);
	gfx_line(150,150,100,100);

	int curr_iters = 5;

	// Draw the mandelbrot set with the passed iterations
	draw_mandelbrot(curr_iters);

	while(1) {
		// Wait for the user to press a character.
		key = gfx_wait();

		// Quit if it is the letter q.
		if(key=='q') break;

		if (key == ' ')	draw_mandelbrot(curr_iters++);
	}

	return 0;
}
