#ifndef COLOR_H
#define COLOR_H

class Color {
private:
    int red;
    int green;
    int blue;

public:
    // Konstruktor
    Color(int r, int g, int b);

    // Gettery
    int getRed() const;
    int getGreen() const;
    int getBlue() const;
};

#endif