#include "stdafx.h"
#include "MotionBlur.h"

float minDistance(int _x1, int _y1, float _angle)
{
	float m_k = tan(_angle * 3.1415926 / 180);
	float m_k1 = tan((_angle + 90) * 3.1415926 / 180);
	float m_x = (_y1 - m_k1 * _x1) / (m_k - m_k1);
	float m_y = m_k * m_x;

	return sqrt(pow(m_x - _x1, 2) + pow(m_y - _y1, 2));
}

int createMotionBlurKernel(Mat& _kernel, int _magnitude, int _angle)
{
	if (_magnitude <= 0)
		return -1;

	int h, w;
	h = ceil(_magnitude * sin(_angle * 3.1415926 / 180));
	w = ceil(_magnitude * cos(_angle * 3.1415926 / 180));
	int kW_half = h > w ? h : w;
	_kernel = Mat::zeros(2 * kW_half + 1, 2 * kW_half + 1, CV_32FC1);
	for (int yy = -1 * kW_half; yy <= kW_half; yy++)
	{
		float *ptr = _kernel.ptr<float>(-1 * yy + kW_half);
		for (int xx = -1 * kW_half; xx <= kW_half; xx++)
		{
			float minD = minDistance(xx, yy, _angle);
			float val = 1 - minD;
			if (val > 0)
				ptr[xx + kW_half] = val;
		}
	}
	Scalar m_sum = sum(_kernel);
	_kernel = _kernel / m_sum[0];

	return 1;
}