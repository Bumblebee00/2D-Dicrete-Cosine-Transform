// TODO:
// - Fix rectangular images
// - Speed up DCT computation
// - Add colors maybe?

// ========== Includes and defines
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define MAX_C 100



// ========== Function prototypes
void save_array_to_file(const char *filename, double *arr, size_t size);
void load_array_from_file(const char *filename, double *arr, size_t size);

// converts a source image (array of width * height * channels elements of type
// unsigned char) to a grayscale image (array of width * height elements)
int convert_to_grayscale(unsigned char* source_img, unsigned char* gray_img, int width, int height, int channels);

// functions to compute the direct and inverse Discrete Cosine Transform
double alpha(int u, int width); // normalization coefficents
int compute_DCT(unsigned char *source_img, double* freq_img, int width, int height);
int reverse_DCT(double* freq_img, unsigned char *img, int width, int height);

// writes to disk a spectrum image (array of width * height elements of type double
int spectrum_write_png(double* freq_img, char* name, int width, int height);

// creates a folder with the bases of the frequency space
int generate_bases(int width, int height);



// ========== Main function
int main(){
    clock_t begin = clock();
    // generate_bases(8, 16);

    const char *name = "gorilla"; // Base name for images
    const char *ext = ".png"; // Extension for images
    char filename[MAX_C];
    sprintf(filename, "%s%s", name, ext);
    char gray_image_name[MAX_C];
    sprintf(gray_image_name, "%s_gray%s", name, ext);
    char spectrum_name[MAX_C];
    sprintf(spectrum_name, "%s_spectrum%s", name, ext);
    char spectrum_bin_name[MAX_C];
    sprintf(spectrum_bin_name, "%s_spectrum.bin", name);
    char modified_spectrum_name[MAX_C];
    sprintf(modified_spectrum_name, "%s_modified_spectrum%s", name, ext);
    char output_name[MAX_C];
    sprintf(output_name, "%s_output%s", name, ext);

//     // load image
//     int width, height, channels;
//     unsigned char *source_img = stbi_load(filename, &width, &height, &channels, 0);
//     if (source_img == NULL){ printf("Error loading image\n"); return 1; }
//     
//     // convert to grayscale
//     unsigned char *gray_img = (unsigned char *)malloc(width * height * sizeof(unsigned char));
//     if (channels == 1){ for (int i=0; i<width*height; i++){ gray_img[i] = source_img[i]; } }
//     else{
//         convert_to_grayscale(source_img, gray_img, width, height, channels);
//         stbi_write_png(gray_image_name, width, height, 1, gray_img, width);
//     }
// 
//     // compute Discrete Cosine Transform
//     double *freq_img = malloc(width * height * sizeof(double));
//     compute_DCT(gray_img, freq_img, width, height);
//     spectrum_write_png(freq_img, spectrum_name, width, height);
//     save_array_to_file(spectrum_bin_name, freq_img, width * height);

    // use this to load a spectrum from .bin file
    int width = 500, height = 500;
    double *freq_img = malloc(width * height * sizeof(double));
    load_array_from_file("gorilla_spectrum.bin", freq_img, width * height);

    // modify spectrum
    for (int v=0; v<height; v++){
        for (int u=0; u<width; u++){
            if (u*u + v*v < 50*50){
                freq_img[u + v*width] = 0;
            }
        }
    }
    spectrum_write_png(freq_img, modified_spectrum_name, width, height);
    
    // compute inverse Discrete Cosine Transform
    unsigned char *img2 = (unsigned char *)malloc(sizeof(unsigned char) * width * height);
    reverse_DCT(freq_img, img2, width, height);
    stbi_write_png(output_name, width, height, 1, img2, width);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Execution time: %f\n", time_spent);    
    return 0;
}










void pb(float progress){
    int pbw = 50; // progress bar width

    printf("\r[");
    for (int i = 0; i < pbw; i++) {
        if (i < pbw * progress){ printf("#"); }
        else{ printf(" "); }
    }
    printf("]");
    fflush(stdout);
}

int convert_to_grayscale(unsigned char* source_img, unsigned char* gray_img, int width, int height, int channels){
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            gray_img[y * width + x ] = (unsigned char)(
                0.299 * source_img[(y * width + x) * channels] +
                0.587 * source_img[(y * width + x) * channels + 1] +
                0.114 * source_img[(y * width + x) * channels + 2]
            );
        }
    }
    printf("Source image converted to grayscale\n");
    return 0;
}

double alpha(int u, int width){
    return u==0 ? sqrt(1.0/width) : sqrt(2.0/width);
}

double compute_DCT_pixel(unsigned char *source_img, int u, int v, int width, int height){
    double r = 0;
    for (int y=0; y<height; y++){
        for (int x=0; x<width; x++){
            r += (source_img[x + y*width] - 128.0) * cos((x + 0.5)*u*M_PI/width) * cos((y + 0.5)*v*M_PI/height);
        }
    }
    return r * alpha(u, width) * alpha(v, height);
}

int compute_DCT(unsigned char *source_img, double* freq_img, int width, int height){
    for (int v=0; v<height; v++){
        for (int u=0; u<width; u++){
            freq_img[u + v*width] = compute_DCT_pixel(source_img, u, v, width, height);
        }
        pb((float)v/height);
    }
    printf("\r%-110s\n", "DCT computation completed");
    
    return 0;
}

unsigned char reverse_DCT_pixel(double *freq_img, int x, int y, int width, int height){
    double r = 0;
    for (int u=0; u<width; u++){
        for (int v=0; v<height; v++){
            r += alpha(u, width) * alpha(v, height) * freq_img[u + v*width] * cos((x + 0.5)*u*M_PI/width) * cos((y + 0.5)*v*M_PI/height);

        }
    }

    return (unsigned char)round(r + 128.0);
}

int reverse_DCT(double* freq_img, unsigned char *img, int width, int height){
    for (int x=0; x<width; x++){
        for (int y=0; y<height; y++){
            img[x + y*width] = reverse_DCT_pixel(freq_img, x, y, width, height);
        }
        pb((float)x/width);
    }

    printf("\r%-110s\n", "Inverse DCT computation completed");
    return 0;
}

// color palette is:
// spectral value = 0:          black
// 0 <= spectral value <= slim: grayscale
// abs(spectral value) > slim:  white
int spectrum_write_png(double* freq_img, char* name, int width, int height){
    double slim = 200;
    unsigned char *simg = malloc(sizeof(unsigned char) * width * height);

    for (int v=0; v<height; v++){
        for (int u=0; u<width; u++){
            double s = (fabs(freq_img[u + width*v]) / slim);
            s = s > 1 ? 1 : s;
            simg[u + width*v] = (unsigned char)round(255 * s);
        }
    }

    stbi_write_png(name, width, height, 1, simg, width);
    printf("Spectrum image written to disk\n");
    return 0;
}

// creates a folder with the bases of the frequency space
int generate_bases(int width, int height){
    char dirname[MAX_C];
    sprintf(dirname, "bases%dx%d", width, height);
    struct stat st = {0};
    if (stat(dirname, &st) == -1) {
        mkdir(dirname, 0700);
    }
    unsigned char *new_img = malloc(sizeof(unsigned char) * width * height);
    for (int y=0; y<height; y++){
        for (int x=0; x<width; x++){
            double *freq_img = calloc(width * height, sizeof(double));
            freq_img[x + width*y] = 100;
    
            reverse_DCT(freq_img, new_img, width, height);
       
            char name[MAX_C];
            sprintf(name, "%s/(%d,%d).png", dirname, x, y);
    
            stbi_write_png(name, width, height, 1, new_img, width);
        }
    }

    return 0;
}


void save_array_to_file(const char *filename, double *arr, size_t size) {
    FILE *file = fopen(filename, "wb");  // Open file for writing in binary mode
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }
    
    fwrite(arr, sizeof(double), size, file);  // Write the array to the file
    fclose(file);  // Close the file
}

void load_array_from_file(const char *filename, double *arr, size_t size) {
    FILE *file = fopen(filename, "rb");  // Open file for reading in binary mode
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    fread(arr, sizeof(double), size, file);  // Read the array from the file
    fclose(file);  // Close the file
}