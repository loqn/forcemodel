#include "Coord.hpp"
#include <cmath>
#include <stdexcept>

#include <cmath>

static Coord origin = Coord();

Coord::Coord() {
  this->x = 0;
  this->y = 0;
}

Coord::Coord(float x, float y) {
  this->x = x;
  this->y = y;
}

float Coord::norm() const {
  return std::sqrt(x * x + y * y);
}

double Coord::distanceFrom(const Coord &c) const {
    return sqrt(pow(c.getX() - getX(), 2) + pow(c.getY() - getY(), 2));
}

//getters/setters
float Coord::getX() const {
  return x;
}

float Coord::getY() const {
  return y;
}

void Coord::setX(float x) {
  this->x = x;
}

void Coord::setY(float y) {
  this->y = y;
}

//operators

bool Coord::operator==(const Coord &c) const {
  return x == c.x && y == c.y;
}

Coord Coord::operator+(const Coord &c) const {
  return Coord(x+c.x, y+c.y);
}

Coord Coord::operator-(const Coord &c) const {
  return Coord(x-c.x, y-c.y);
}

Coord& Coord::operator+=(const Coord &c) {
  x += c.x;
  y += c.y;
  return *this;
}

Coord& Coord::operator-=(const Coord &c) {
  x -= c.x;
  y -= c.y;
  return *this;
}

Coord Coord::operator*(const double &f) const {
  return Coord(x*f, y*f);
}

Coord Coord::operator/(const double &f) const {
  if (f == 0) {
    throw std::invalid_argument("Division by zero!");
  }
  return Coord(x/f, y/f);
}

Coord& Coord::operator*=(const float &f) {
  x *= f;
  y *= f;
  return *this;
}

Coord& Coord::operator/=(const float &f) {
  if (f == 0) {
    throw std::invalid_argument("Division by zero!");
  }
  x /= f;
  y /= f;
  return *this;
}

//tab

float& Coord::operator[](int dim) {
  if (dim == 0) {
    return x;
  } else if (dim == 1) {
    return y;
  } else {
    throw std::out_of_range("Index out of range!");
  }
}

float Coord::operator[](int dim) const {
  if (dim == 0) {
    return x;
  } else if (dim == 1) {
    return y;
  } else {
    throw std::out_of_range("Index out of range!");
  }
}

