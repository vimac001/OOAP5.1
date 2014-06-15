#ifndef COLOR_HPP
#define COLOR_HPP

#include <string>
#include <cv.h>

class Color
{
protected:
	unsigned char red, green, blue;
	double alpha;

	static const unsigned int redFilter = 0xff, greenFilter = 0xff00, blueFilter = 0xff0000;

	void initColor(unsigned int clr, double alpha){
		this->red = clr & 0xff;
		this->green = (clr >> 8) & 0xff;
		this->blue = (clr >> 16) & 0xff;

		this->alpha = alpha;
	}

public:
	Color(){
		this->red = 0;
		this->green = 0;
		this->blue = 0;
		this->alpha = 1;
	}

	Color(unsigned char red, unsigned char green, unsigned char blue, double alpha = 1){
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}

	Color(unsigned int clr, double alpha = 1){
		this->initColor(clr, alpha);
	}

	Color(int clr, double alpha = 1){
		this->initColor(clr, alpha);
	}

	Color(double dclr){
		unsigned int clr = (unsigned int)dclr;
		this->initColor(clr, dclr - clr);
	}
	
	void setRed(unsigned char val){
		this->red = val;
	}

	void setGreen(unsigned char val){
		this->green = val;
	}

	void setBlue(unsigned char val){
		this->blue = val;
	}

	void setAlpha(double alpha){
		this->alpha = alpha;
	}

	Color& operator= (const unsigned int rhs){
		this->initColor(rhs, this->alpha);
		return *this;
	}

	Color& operator= (const double rhs){
		unsigned int clr = (unsigned int)rhs;
		this->initColor(clr, rhs - clr);
		return *this;
	}


	operator cv::Scalar(){
		return cv::Scalar(this->red, this->green, this->blue);
	}
};

#endif