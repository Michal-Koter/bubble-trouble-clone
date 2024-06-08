//
// Created by koter on 08.06.2024.
//

#ifndef MYGAME_VECTOR2D_H
#define MYGAME_VECTOR2D_H

#include <iostream>

class Vector2D {
public:
    double x, y;

    Vector2D();
    Vector2D(double x, double y);

    Vector2D& Add(const Vector2D& vec);
    Vector2D& Subtract(const Vector2D& vec);
    Vector2D& Multiply(const Vector2D& vec);
    Vector2D& Divide(const Vector2D& vec);

    friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

    Vector2D& operator+=(const Vector2D& vec);
    Vector2D& operator-=(const Vector2D& vec);
    Vector2D& operator*=(const Vector2D& vec);
    Vector2D& operator/=(const Vector2D& vec);

    friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};


#endif //MYGAME_VECTOR2D_H
