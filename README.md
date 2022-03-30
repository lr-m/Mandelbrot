# C_Mandelbrot
Visualisation of the mandelbrot set using C, uses the unoptimised escape time algorithm.

Simple graphics library utilised: https://www3.nd.edu/~dthain/courses/cse20211/fall2013/gfx/

## Dependencies

*X11/Xlib.h*

Install with (Ubuntu):
`sudo apt install libx11-dev`

## Compilation

`gcc mandelbrot.c gfx.c -o example -lX11 -lm`

## Controls
- Space: Increases the iteration count of the visualisation

## Produced visualisation

<img src="https://user-images.githubusercontent.com/47477832/160488734-5c78686f-ee5b-43b0-8d05-91a6889fc63b.png" width="700">
