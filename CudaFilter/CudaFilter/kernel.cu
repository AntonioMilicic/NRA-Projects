#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "lodepng.h"
#include <iostream>

__global__
void filter(unsigned char* input_image, unsigned char* output_image, int width, int height) {
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int row = blockIdx.y * blockDim.y + threadIdx.y;

	if (row < 2 || col < 2 || row >= height - 3 || col >= width - 3)
		return;

	// GAUSS BLUR / 16
	float kernel[3][3] = {
		{ 1, 2, 1 },
		{ 2, 4, 2 },
		{ 1, 2, 1 }
	};

	int sum = 0;
	int kernelSum = 0;
	for (int j = -1; j <= 1; j++) {
		for (int i = -1; i <= 1; i++)
		{
			int pixel = input_image[(row + j) * width + (col + i)];
			int val = pixel * kernel[i + 1][j + 1];
			sum += val;
			kernelSum += kernel[i][j];
		}
	}

	int value = sum / (kernelSum);
	output_image[row * width + col] = (value > 0) ? value : 0;
}


void convolution(unsigned char* input_image, unsigned char* output_image, int width, int height) {

	unsigned char* dev_input;	// declare arrays for pixels from image
	unsigned char* dev_output;	// same

	cudaMalloc((void**)&dev_input, width*height * sizeof(unsigned char));	// Alocate memory on cuda with size of image, each pixel is char with color value(num)
	cudaMalloc((void**)&dev_output, width*height * sizeof(unsigned char));	// Alocate memory for image output

	cudaMemcpy(dev_input, input_image, width*height * sizeof(unsigned char), cudaMemcpyHostToDevice);	// Copying input array, pixels of image on cuda memory

	dim3 blockDims(32, 32);	// define size of blocks which we sent to cuda thread
	dim3 gridDims(width / 32, height / 32);	// define grid, grid and blocks define size of each data on each cuda thread

	filter <<< gridDims, blockDims >>> (dev_input, dev_output, width, height);	// Call filter method for each thread, defined by block and grid size
	cudaThreadSynchronize();	// waiting for all threads to finish job

	cudaMemcpy(output_image, dev_output, width*height * sizeof(unsigned char), cudaMemcpyDeviceToHost);	// copy the output image(array of pixels) from cuda memory to cpu memory

	cudaFree(dev_input);	// free arrays
	cudaFree(dev_output);
}