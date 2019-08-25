#include <iostream>
#include <algorithm>
#include <random>

#include <cmath>

#include "Surface.h"

bool Line(Surface24& S, const Surface24::RGB& Color, Surface24::Cood x0, Surface24::Cood y0,Surface24::Cood x1,  Surface24::Cood y1) {//ƒuƒŒƒ[ƒ“ƒnƒ€Line
	bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
	if (steep) {
		std::swap(x0, y0);
		std::swap(x1, y1);
	}
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int deltax = x1 - x0;
	int deltay = std::abs(y1 - y0);
	int error = deltax / 2;
	int ystep = 0;
	int y = y0;
	if (y0 < y1) { ystep = 1; }
	else { ystep = -1; }
	for (int x = x0; x < x1; x ++) {
		if (steep) {
			S.Index(y, x) = Color;
		}
		else {
			S.Index(x, y) = Color;
		}
		error = error - deltay;
		if (error < 0) {
			y = y + ystep;
			error = error + deltax;

		}
	}
	return true;
}

int main() {

	std::random_device rd;
	std::minstd_rand mr(rd());
	std::mt19937 mt;
	std::uniform_int_distribution<std::uint16_t> ui(0, 255);

	std::intmax_t C = 16;
	std::intmax_t L = 120;
	Surface24 S(256, 256);

	double x1 = 0;
	double x2 = 0;
	double y1 = 0;
	double y2 = L;
	double rad = 3.1415926434/180.0;

	double Angle = 0;
	for (std::size_t X = 0; X <= C; X++) {
		x1 = x2;
		y1 = y2;
		x2 = L * std::sin(rad * Angle);
		y2 = L * std::cos(rad * Angle);
		//Angle += (360.0) / (C);
		Angle += (360.0) / (C);
		Angle = std::fmod(Angle, 360.0);
		Line(S, { (std::uint8_t)ui(mr),(std::uint8_t)ui(mr),(std::uint8_t)ui(mr) }, x1+S.Width()/2, y1+S.Height()/2, x2+S.Width()/2, y2+S.Height()/2);
	}

	SaveBMP(S, "test.bmp");

	return 0;




}