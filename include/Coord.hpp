#ifndef COORD_H
#define COORD_H

class Coord {
  public:
    Coord();
    Coord(float x, float y);
    float norm() const;

    //getters/setters
    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);

    double distanceFrom(const Coord &c) const;

    //operators
    bool operator==(const Coord &c) const;
    Coord operator+(const Coord &c) const;
    Coord operator-(const Coord &c) const;
    Coord& operator+=(const Coord &c);
    Coord& operator-=(const Coord &c);
    Coord operator*(const double &f) const;
    Coord operator/(const double &f) const;
    Coord& operator*=(const float &f);
    Coord& operator/=(const float &f);

    //tab
    float & operator[](int dim);
    float operator[](int dim) const;
  private:
    float x;
    float y;
};
#endif
