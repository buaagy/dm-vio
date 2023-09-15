/**
* This file is part of DSO.
*
* Copyright 2016 Technical University of Munich and Intel.
* Developed by Jakob Engel <engelj at in dot tum dot de>,
* for more information see <http://vision.in.tum.de/dso>.
* If you use this code, please cite the respective publications as
* listed on the above website.
*
* DSO is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* DSO is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with DSO. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include <cstring>
#include <iostream>

namespace dso
{
class ImageAndExposure
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	float* image;        // 辐照度图像,取值在0～256
	int w,h;	         // 图像宽度,高度
	double timestamp;    // 时间戳
	float exposure_time; // 曝光时间,单位毫秒
	
	// 构造函数
	inline ImageAndExposure(int w_, int h_, double timestamp_=0) : w(w_), h(h_), timestamp(timestamp_)
	{
		image = new float[w*h];
		exposure_time=1;
	}
	
	// 析构函数
	inline ~ImageAndExposure()
	{
		delete[] image;
	}
	
	// 复制曝光时间给其他图像
	inline void copyMetaTo(ImageAndExposure &other)
	{
		other.exposure_time = exposure_time;
	}
	
	// 深拷贝
	inline ImageAndExposure* getDeepCopy()
	{
		ImageAndExposure* img = new ImageAndExposure(w,h,timestamp);
		img->exposure_time = exposure_time;
		memcpy(img->image, image, w*h*sizeof(float));
		return img;
	}
};
}
