#include "Shape.h"
#include <stdexcept>

// Método auxiliar: comprobar color válido
bool Shape::valid_color(const std::string &c) {
    return c == "red" || c == "green" || c == "blue";
}

// Constructor por defecto
Shape::Shape() : color("red") {}

// Constructor con color
Shape::Shape(std::string color) {
    if (!valid_color(color)) {
        throw std::invalid_argument("Color no valido");
    }
    this->color = color;
}

// Getter
std::string Shape::get_color() const {
    return color;
}

// Setter
void Shape::set_color(std::string c) {
    if (!valid_color(c)) {
        throw std::invalid_argument("Color no valido");
    }
    color = c;
}

