#include "Square.h"

// Cuadrado válido si todas las aristas tienen la misma longitud:
// |v0-v1| == |v1-v2| == |v2-v3| == |v3-v0|
bool Square::check(Point2D* vertices) {
    if (vertices == nullptr) return false;

    double a = Point2D::distance(vertices[0], vertices[1]);
    double b = Point2D::distance(vertices[1], vertices[2]);
    double c = Point2D::distance(vertices[2], vertices[3]);
    double d = Point2D::distance(vertices[3], vertices[0]);

    return (a == b) && (b == c) && (c == d);
}

Square::Square() : Rectangle() {
    // sustituimos los vértices por los del cuadrado por defecto
    Point2D vertices[N_VERTICES] = {
        Point2D(-1,  1),
        Point2D( 1,  1),
        Point2D( 1, -1),
        Point2D(-1, -1)
    };
    // usa el set_vertices del cuadrado (valida cuadrado)
    set_vertices(vertices);
}

Square::Square(std::string color, Point2D* vertices) : Rectangle(color, vertices) {
    // El ctor de Rectangle solo valida rectángulo; aquí validamos cuadrado:
    if (!check(vertices)) {
        throw std::invalid_argument("Vertices no forman un cuadrado valido");
    }
    // Aseguramos que se copien (y queden validados como cuadrado)
    set_vertices(vertices);
}

void Square::set_vertices(Point2D* vertices) {
    if (!check(vertices)) {
        throw std::invalid_argument("Vertices no forman un cuadrado valido");
    }
    // Reutilizamos la lógica de Rectangle para copiar los 4 vértices
    Rectangle::set_vertices(vertices);
}

void Square::print() {
    std::cout << *this;
}

std::ostream& operator<<(std::ostream &out, const Square &square) {
    out << "[Square: color = " << square.get_color() << "; vertices = {";
    for (int i = 0; i < Square::N_VERTICES; ++i) {
        out << square.vs[i];
        if (i != Square::N_VERTICES - 1) out << ", ";
    }
    out << "}]";
    return out;
}

