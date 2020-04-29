// blur_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "MotionBlur.h"
using namespace std;

int _tmain(int argc, char* argv[])
{
	Mat m_kernel;

	if (2 != argc)
	{
		cout << "usage: blur_test  imagename";
		return 0;
	}



	int res = createMotionBlurKernel(m_kernel, 3, 30);
	if (res < 0)
	{
		printf("create kernel error!\n");
		return -1;
	}

	Mat srcImg = imread(argv[1]);
	Mat dstImg;
	filter2D(srcImg, dstImg, -1, m_kernel);
	string window_name = "haha...";
	namedWindow(window_name);
	imshow(window_name, dstImg);
	waitKey(0);
	return 0;
}

