#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdexcept>
#include <iostream>
#include "Shape.h"
#include "Point2D.h"

class Rectangle : public Shape {
protected:
    Point2D* vs; // array dinámico de 4 vértices

private:
    static bool check(Point2D* vertices);

public:
    static int const N_VERTICES = 4;

    Rectangle();
    Rectangle(std::string color, Point2D* vertices);
    Rectangle(const Rectangle &r);
    ~Rectangle() override;

    Point2D get_vertex(int ind) const;
    Point2D operator[](int ind) const;

    virtual void set_vertices(Point2D* vertices);

    Rectangle& operator=(const Rectangle &r);

    double area() const override;
    double perimeter() const override;
    void translate(double incX, double incY) override;

    virtual void print() override;

    friend std::ostream& operator<<(std::ostream &out, const Rectangle &r);
};

#endif

