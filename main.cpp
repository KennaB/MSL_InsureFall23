#include <iostream>
#include <gperftools/profiler.h>
#include <png.h>
#include <complex>
#include <vector>
#include <fstream>

using namespace std;

// Constants for Mandelbrot generation
const int WIDTH = 800;
const int HEIGHT = 800;
const int MAX_ITER = 1000;  // Maximum number of iterations for Mandelbrot calculation

// Helper function to determine if a point is in the Mandelbrot set
int mandelbrot(double real, double imag) {
    std::complex<double> z(0, 0);
    std::complex<double> c(real, imag);
    
    for (int i = 0; i < MAX_ITER; ++i) {
        z = z * z + c;
        if (std::abs(z) > 2.0) {
            return i;  // Return number of iterations before escape
        }
    }
    return MAX_ITER;  // Point is likely in the Mandelbrot set
}

// Generate the Mandelbrot set and output to a PGM file (simple grayscale image format)
void generate_mandelbrot() {
    std::vector<std::vector<int>> image(WIDTH, std::vector<int>(HEIGHT));

    // Generate the Mandelbrot image
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            double real = (x - WIDTH / 2.0) * 4.0 / WIDTH;
            double imag = (y - HEIGHT / 2.0) * 4.0 / HEIGHT;
            int value = mandelbrot(real, imag);
            image[x][y] = (value == MAX_ITER) ? 0 : (value % 256);  // Color mapping
        }
    }

    // Save the image to a PGM file
    std::ofstream file("mandelbrot.pgm");
    file << "P2\n" << WIDTH << " " << HEIGHT << "\n255\n";  // PGM header
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            file << image[x][y] << " ";
        }
        file << "\n";
    }
    file.close();
    // Save the image to a PNG file
    FILE *fp = fopen("mandelbrot.png", "wb");
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);

    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr, info_ptr, WIDTH, HEIGHT,
                 8, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr, info_ptr);

    for (int y = 0; y < HEIGHT; ++y) {
        png_bytep row = (png_bytep) malloc(3 * WIDTH * sizeof(png_byte));
        for (int x = 0; x < WIDTH; ++x) {
            row[x] = image[x][y];
        }
        png_write_row(png_ptr, row);
        free(row);
    }

    png_write_end(png_ptr, NULL);
    fclose(fp);

    if (png_ptr && info_ptr) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
    }
}

int fibonacci_recursive_1(int n);
int fibonacci_recursive_2(int n);

int fibonacci(int n) {
    if (n <= 1)
        return n;

    int result1 = fibonacci_recursive_1(n-1);
    int result2 = fibonacci_recursive_2(n-2);

    return result1 + result2;
}

int fibonacci_recursive_1(int n) {
    if (n <= 1)
        return n;
    return fibonacci(n-1);
}

int fibonacci_recursive_2(int n) {
    if (n <= 1)
        return n;
    return fibonacci(n-2);
}

int main() {
    int n = 70; // Adjusted this for more computation

    // Start the profiler and save the output to a file named "combined.prof"
    ProfilerStart("combined.prof");
    
    // Run Fibonacci multiple times
    for (int i = 0; i < 10; ++i) {
        cout << "Fibonacci(" << n << ") = " << fibonacci(n) << endl;
    }

    generate_mandelbrot();

    // Stop the profiler
    ProfilerStop();

    return 0;
}
