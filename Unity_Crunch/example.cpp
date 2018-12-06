// File: example.cpp - Sample usage of a CrunchObject

#include "CrunchObject.h"
#include "windows.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	CrunchObject* crunchObj = new CrunchObject();
	crunchObj->compress("C:/Users/TY/Desktop/Newfolder/001.jpg", 500, 730);
	crunchObj->decompress_write("C:/Users/TY/Desktop/Newfolder/001.crn");
	delete crunchObj;
	return EXIT_SUCCESS;
}
