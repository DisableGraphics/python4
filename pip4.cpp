#include <chrono>
#include <climits>
#include <iostream>
#include <thread>
#include <cmath>
#include <vector>
#include <cstring>

std::vector<std::string> pip4_failures = {
    "Error: Network connection lost. Please try again.",
    "Error: Package not found. Please check the package name and try again.",
    "Error: Insufficient permissions to install package.",
    "Error: Dependency conflict detected. Unable to resolve dependencies.",
    "Error: Download failed due to server timeout.",
    "Error: Disk space insufficient. Free up space and try again.",
    "Error: Invalid package version specified.",
    "Error: Unable to verify package integrity. Download might be corrupted.",
    "Error: Proxy authentication required.",
    "Error: SSL certificate verification failed.",
    "Error: Package requires Python3, but only Python4 is installed.",
    "Error: Repository unavailable. Please check your sources list.",
    "Error: No internet connection detected.",
    "Error: Package installation canceled by user.",
    "Error: Required package 'setuptools' not found.",
    "Error: Conflicting versions of package already installed.",
    "Error: This package is no longer supported.",
    "Error: Package requires unsupported OS version.",
    "Error: Cannot install package in a virtual environment.",
    "Error: Package repository is down for maintenance.",
    "Error: Package download quota exceeded.",
    "Error: Incorrect package hash. The file may have been tampered with.",
    "Error: Package installation locked by another process.",
    "Error: Unable to access local package cache.",
    "Error: Package metadata could not be read."
};


void backspace(int j) {
	int ndigits = j == 0 ? 1 : std::log10(j) + 1;
	for(int i = 0; i < 80 + ndigits + 1; i++) {
		std::cout << '\b';
	}
	std::cout.flush();
}

int main(int argc, char ** argv) {
	std::srand(std::time(nullptr));
	if(argc < 3) {
		std::cout << "Usage: " << argv[0] << " install <packages>\n";
		return EXIT_FAILURE;
	}
	for(int i = 2; i < argc; i++) {
		std::cout << "Downloading " << argv[i] << std::endl;
		std::cout << "Estimated size: " << std::strlen(argv[i]) * 14.52 << " GB\n";
		for(int j = 0; j < 101; j++) {
			double fraction = ((double)j / 101) * 80;
			for(int k = 0; k < 80; k++) {
				if(k < fraction)
					std::cout << "#";
				else
					std::cout << ".";
			}
			std::cout << j << "%";
			std::cout.flush();
			if(rand() < (INT_MAX / 16)) {
				// Simulate rare hung process
				std::this_thread::sleep_for(std::chrono::minutes(30));
			}
			std::this_thread::sleep_for(std::chrono::minutes(1));
			if(j != 100 ) backspace(j);
		}
	}

	size_t failure_cause = rand() % pip4_failures.size();

	throw std::runtime_error(pip4_failures[failure_cause]);
}