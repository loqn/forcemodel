#include "Color.hpp"
#include <stdexcept>

Color::Color() {
  r = 0;
  g = 0;
  b = 0;
  alpha = 0;
}

Color::Color(int r, int g, int b, int alpha) {
  this-> r = r;
  this-> g = g;
  this-> b = b;
  this-> alpha = alpha;
}

int Color::getR() {
  return r;
}

int Color::getG() {
  return g;
}

int Color::getB() {
  return b;
}

int Color::getAlpha() {
  return alpha;
}

Color Color::interpolate(const Color &c, float ratio) {
  float r = ratio;
  if (r < 0) r = 0;
  if (r > 1) r = 1;

  int new_r = this->r + (c.r - this->r) * r;
  int new_g = this->g + (c.g - this->g) * r;
  int new_b = this->b + (c.b - this->b) * r;
  int new_alpha = this->alpha + (c.alpha - this->alpha) * r;

  return Color(new_r, new_g, new_b, new_alpha);
}


const int& Color::operator[](int canal) const {
  switch (canal) {
    case 0:
      return r;
    case 1:
      return g;
    case 2:
      return b;
    case 3:
      return alpha;
    default:
      throw std::out_of_range("[OUT_OF_RANGE] Non-existing canal.");
  }
}

int& Color::operator[](int canal) {
  switch (canal) {
    case 0:
      return r;
    case 1:
      return g;
    case 2:
      return b;
    case 3:
       return alpha;
    default:
      throw std::out_of_range("[OUT_OF_RANGE] Non-existing canal.");
  }
}

bool Color::operator==(const Color &c) const {
  return r == c.r && g == c.g && b == c.b && alpha == c.alpha;
}