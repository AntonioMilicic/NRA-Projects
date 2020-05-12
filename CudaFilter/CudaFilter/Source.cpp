#include "lodepng.h"
#include <iostream>
#include "kernel.h"


int main()
{
	vector<unsigned char> in_image;
	unsigned int width, height;
    int where = 0; //  pointing to the current pixel in RGB arrays

	// Load image
	unsigned error = lodepng::decode(in_image, width, height, "inputImage.png");
	if (error) cout << "decoder error " << error << ": " << endl;

	// Data allocation
	unsigned char* input_image = new unsigned char[(in_image.size() * 3) / 4];
	unsigned char* output_image = new unsigned char[(in_image.size() * 3) / 4];

	unsigned char* input_imageR = new unsigned char[in_image.size() / 4];
	unsigned char* input_imageG = new unsigned char[in_image.size() / 4];
	unsigned char* input_imageB = new unsigned char[in_image.size() / 4];

	unsigned char* output_imageR = new unsigned char[in_image.size() / 4];
	unsigned char* output_imageG = new unsigned char[in_image.size() / 4];
	unsigned char* output_imageB = new unsigned char[in_image.size() / 4];
	

	for (int i = 0; i < in_image.size(); i=i+4) {
		// Pull each RGB pixel to its array
		input_imageR[where] = in_image.at(i);
		input_imageG[where] = in_image.at(i+1);
		input_imageB[where] = in_image.at(i+2);
		where++;
	}

	// Run convoluton on each color array
	convolution(input_imageR, output_imageR, width, height);
	convolution(input_imageG, output_imageG, width, height);
	convolution(input_imageB, output_imageB, width, height);

	// Merging all RGB pixels back to output image
	vector<unsigned char> out_image;
	for (int i = 0; i < ( (in_image.size() * 3) / 12); ++i) {
		out_image.push_back(output_imageR[i]);
		out_image.push_back(output_imageG[i]);
		out_image.push_back(output_imageB[i]);
		out_image.push_back(255); // Alpha ( PNG is RGBA format) 
	}

	// Save output image
	error = lodepng::encode("outputImage.png", out_image, width, height);

	if (error) std::cout << "encoder error " << error << ": " << std::endl;

	delete[] input_image;
	delete[] output_image;
	return 0;
}
