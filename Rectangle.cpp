#include "Rectangle.h"
#include <cmath>

// Un rectángulo es válido si:
// |v0-v1| == |v2-v3|  y  |v1-v2| == |v3-v0|
bool Rectangle::check(Point2D* vertices) {
    if (vertices == nullptr) return false;

    double a = Point2D::distance(vertices[0], vertices[1]);
    double b = Point2D::distance(vertices[2], vertices[3]);
    double c = Point2D::distance(vertices[1], vertices[2]);
    double d = Point2D::distance(vertices[3], vertices[0]);

    return (a == b) && (c == d);
}

Rectangle::Rectangle() : Shape(), vs(new Point2D[N_VERTICES]) {
    vs[0] = Point2D(-1,  0.5);
    vs[1] = Point2D( 1,  0.5);
    vs[2] = Point2D( 1, -0.5);
    vs[3] = Point2D(-1, -0.5);
}

Rectangle::Rectangle(std::string color, Point2D* vertices) : Shape(color), vs(new Point2D[N_VERTICES]) {
    if (!check(vertices)) {
        delete[] vs;
        vs = nullptr;
        throw std::invalid_argument("Vertices no forman un rectangulo valido");
    }
    for (int i = 0; i < N_VERTICES; ++i) vs[i] = vertices[i];
}

Rectangle::Rectangle(const Rectangle &r) : Shape(r.color), vs(new Point2D[N_VERTICES]) {
    for (int i = 0; i < N_VERTICES; ++i) vs[i] = r.vs[i];
}

Rectangle::~Rectangle() {
    delete[] vs;
    vs = nullptr;
}

Point2D Rectangle::get_vertex(int ind) const {
    if (ind < 0 || ind >= N_VERTICES) throw std::out_of_range("Indice de vertice fuera de rango");
    return vs[ind];
}

Point2D Rectangle::operator[](int ind) const {
    return get_vertex(ind);
}

void Rectangle::set_vertices(Point2D* vertices) {
    if (!check(vertices)) {
        throw std::invalid_argument("Vertices no forman un rectangulo valido");
    }
    for (int i = 0; i < N_VERTICES; ++i) vs[i] = vertices[i];
}

Rectangle& Rectangle::operator=(const Rectangle &r) {
    if (this == &r) return *this;

    // copiar color (protected en Shape)
    this->color = r.color;

    // asegurar copia segura del array
    if (vs == nullptr) {
        vs = new Point2D[N_VERTICES];
    }
    for (int i = 0; i < N_VERTICES; ++i) vs[i] = r.vs[i];

    return *this;
}

double Rectangle::perimeter() const {
    double side1 = Point2D::distance(vs[0], vs[1]);
    double side2 = Point2D::distance(vs[1], vs[2]);
    return 2 * (side1 + side2);
}

double Rectangle::area() const {
    double side1 = Point2D::distance(vs[0], vs[1]);
    double side2 = Point2D::distance(vs[1], vs[2]);
    return side1 * side2;
}

void Rectangle::translate(double incX, double incY) {
    for (int i = 0; i < N_VERTICES; ++i) {
        vs[i].x += incX;
        vs[i].y += incY;
    }
}

void Rectangle::print() {
    std::cout << *this;
}

std::ostream& operator<<(std::ostream &out, const Rectangle &r) {
    out << "[Rectangle: color = " << r.get_color() << "; vertices = {";
    for (int i = 0; i < Rectangle::N_VERTICES; ++i) {
        out << r.vs[i];
        if (i != Rectangle::N_VERTICES - 1) out << ", ";
    }
    out << "}]";
    return out;
}

