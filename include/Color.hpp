#ifndef COLOR_H
#define COLOR_H

class Color {
  public:
    Color();
    Color(int r, int g, int b, int alpha);
    Color interpolate(const Color &c, float ratio);
    int getR();
    int getG();
    int getB();
    int getAlpha();
    const int& operator[](int canal) const;
    int& operator[](int canal);
    bool operator==(const Color &c) const;
  private:
    int r;
    int g;
    int b;
    int alpha;
};
#endif
