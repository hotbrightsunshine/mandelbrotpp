# 🪄 Mandelbrotpp 

Mandelbrotpp is an interactive Mandelbrot set visualizer written in C++. 
It is still extremely inefficient and needs to be optimized, but I am working to get it usable. 
Working with a really small section of the complex plane is really intensive, because more CPU cores are involved
when dealing with really small doubles. 

## Usage

To run Mandelbrotpp, SDL2 is required in your system. Install it following the instructions in the official website. 

Linux users can run `make run` to build and run the project using `g++`. Windows and Mac OS X users might use a different compiler: follow their instructions accordingly. 

## Memory

Memory usage still heavily depends on the resolution of the SDL window. In fact, each pixel is associated with 
a complex number and a number of iterations (those are needed to decide how to paint each pixel). 
It is, in a way, exponenxial.

## Interactivity

Users can interact with the Mandelbrot visualizer using the following keys. 

| Key | Action |
| - | - |
| `Up Arrow` | Move Up |
| `Left Arrow` | Move Left |
| `Right Arrow` | Move Right | 
| `Down Arrow` | Move Down |
| `I` | Zoom In |
| `O` | Zoom Out |

The visualizer can be close, by closing the SDL window, clicking the appropriate X on top of it. 

## Mechanics 

Once run, the program generates a height * width 2-dimensional vector. 

$z_{\text{min}} = a +bi$ and $z_{\text{out}} = c+di$ are the points in which is calculated the Mandelbrot set. $h$ is the height and $w$ is the width of the window in pixels.

The distance between the two points, hence the size of the complex set to be calculated, is expressed by:

$$
d_{\mathbb{R}} = |a| + |c| 
$$

$$
d_{\mathbb{C}} = (|b| + |d|)i
$$

The percentage (expressed in the range $[0, 1]$) of the distance between 0 and `width` of a given point $x$ is:

$$
    x_p = \frac{x - \frac{|a| + |c|}{2}}{w}; \quad y_p = \frac{y- \frac{|b|+|d|}{2}}{h}.
$$

The program associates each pixel to a complex number, according to these calculations. 

Given the linear interpolation function 

$$
    \text{lerp}(a, b, t) = a+t(b-a),
$$

the associated complex number is

$$
    c = \text{Re } \text{lerp}(a, c, x_p) + \text{Im } \text{lerp}(b, d, y_p).
$$

$$
    c = \text{Re } [a + x_p(c - a)] + \text{Im } [b + y_p(d -b)]
$$

The following are the calculations done for the real part of the number. Accordingly, variables can be substited to obtain the formula for the imaginary part as well. 

$$
    \text{Re } c = a + c\bigg[\frac{x - \frac{|a| + |c|}{2}}{w}\bigg] - a\bigg[\frac{x - \frac{|a| + |c|}{2}}{w}\bigg]
$$

$$
    = a + \frac{c}{w}\bigg(x - \frac{|a| + |c|}{2}\bigg) - \frac{a}{w}\bigg(x - \frac{|a| + |c|}{2}\bigg)
$$

$$
    = a + \bigg(\frac{c}{w}- \frac{a}{w}\bigg)\bigg(x - \frac{|a| + |c|}{2}\bigg)
$$

$$
    = a + \frac{c-a}{2w}\bigg[ 2x - (|a| + |c|) \bigg]
$$

## Next improvements

To improve the performance and the overall usability of Mandelbrotpp, I have decided to:
-  [ ] **Create a configuration file** to customize the global variales of my program. Values such as `HEIGHT` or `THRESHOLD` need to be changed by the user. 
-  [ ] Support for **rectangular resolutions** different from 1x1 resolutions. 
-  [ ] Create a **caching system** that is able to memorize already memorized pixels, in order to render only the ones that the program didn't render. E.g.: when translating the complex plane (i.e. moving with directional arrows), pixels are always re-rendered. This is wrong, because $[-2 -2i, 2 + 2i] \cap [-2.1 -2i, 2.1 + 2i]$ is a really big set of numbers that should be memorized by the program. 
-  [ ] Introduce **GPU calculation**.
-  [ ] Enable **multi-threading** calculations to fasten up the overall process. 
-  [ ] Scale the window for big resolutions, so that almost invisible pixels are not included in the calculations. 
-  [ ] Once implemented the Scale functionality, the program may start rendering the Mandelbrot set with a low resolution, so that panning and zooming are less expensive. Inspiration: [Reddit](https://www.reddit.com/r/math/comments/15h4lmt/broken_mandelbrot_set_looks_awesome_would_this/). 
-  [x] Once the vector is initialized, only its values should change; the vector shall not be initialized once again at every calculation. 

## Preview

This is a preview video of the first v1-alpha version of Mandelbrotpp. 

https://github.com/hotbrightsunshine/mandelbrotpp/assets/36592968/6f49afa9-4ff9-45e9-abe2-0ed5149d2f0f

