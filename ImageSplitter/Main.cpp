#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
namespace fs = std::filesystem;


// please add all these functions to a class

cv::Mat LoadImage(std::string image_path) { return cv::imread(image_path); }

void DisplayImage(cv::Mat input_image, std::string window_title = "Image") {
	cv::imshow(window_title, input_image);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

bool PerfectSplit(cv::Mat input_image, int segments) { return !(input_image.size().height % segments); }

int ImageSplit(cv::Mat input_image, int segments) { return input_image.size().height / segments; }

std::string GetFileName(std::string file_path) { return fs::path(file_path).stem().string(); }

std::string GetFileExtension(std::string file_path) { return fs::path(file_path).extension().string(); }

int main(int argc, char* argv[]) {

	if (argc != 2) {
		std::cout << "Drag one image file on this program to proceed.\n";
		system("pause");
		return 1;
	}
	std::string image_path = argv[1];
	std::string image_name = GetFileName(image_path);
	cv::Mat orignal_image = LoadImage(image_path);

	int segments;
	std::cout << "How many image segments: ";
	std::cin >> segments;

	int segment_length = ImageSplit(orignal_image, segments);

	fs::create_directory(image_name);

	int position = 0;
	for (int i = 0; i < segments; i++) {
		cv::Mat cropped_image = orignal_image(cv::Range(position, position + segment_length), cv::Range(0, orignal_image.size().width));
		position += segment_length;
		imwrite(image_name + "\\" + std::to_string(i + 1) + GetFileExtension(image_path), cropped_image);
	}

}
