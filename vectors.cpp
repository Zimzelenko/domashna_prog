#include <iostream>
#include <cmath>
using namespace std;

double roundToZero(double value) {
    if (abs(value) < 1e-10) return 0;
    return value;
}

struct Point {
    double e[4] = {0};

    Point(double x = 0, double y = 0, double z = 0, double w = 1) {
        e[0] = x;
        e[1] = y;
        e[2] = z;
        e[3] = w;
    }
};

struct Matrix {
    double m[4][4] = {0};

    Matrix() {
        for (int i = 0; i < 4; i++) {
            m[i][i] = 1;
        }
    }

    Matrix operator*(const Matrix &second) const {
        Matrix result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = 0;
                for (int k = 0; k < 4; k++) {
                    result.m[i][j] += m[i][k] * second.m[k][j];
                }
            }
        }
        return result;
    }

    Point operator*(const Point &second) const {
        Point result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.e[i] += m[i][j] * second.e[j];
            }
        }
        return result;
    }

    static Matrix translate(double tx, double ty, double tz) {
        Matrix mat;
        mat.m[0][3] = tx;
        mat.m[1][3] = ty;
        mat.m[2][3] = tz;
        return mat;
    }

    static Matrix scale(double sx, double sy, double sz) {
        Matrix mat;
        mat.m[0][0] = sx;
        mat.m[1][1] = sy;
        mat.m[2][2] = sz;
        return mat;
    }

    static Matrix rotateX(double angle) {
        Matrix mat;
        double rad = angle * M_PI / 180.0;
        mat.m[1][1] = cos(rad);
        mat.m[1][2] = -sin(rad);
        mat.m[2][1] = sin(rad);
        mat.m[2][2] = cos(rad);
        return mat;
    }

    static Matrix rotateY(double angle) {
        Matrix mat;
        double rad = angle * M_PI / 180.0;
        mat.m[0][0] = cos(rad);
        mat.m[0][2] = sin(rad);
        mat.m[2][0] = -sin(rad);
        mat.m[2][2] = cos(rad);
        return mat;
    }

    static Matrix rotateZ(double angle) {
        Matrix mat;
        double rad = angle * M_PI / 180.0;
        mat.m[0][0] = cos(rad);
        mat.m[0][1] = -sin(rad);
        mat.m[1][0] = sin(rad);
        mat.m[1][1] = cos(rad);
        return mat;
    }
};

ostream &operator<<(ostream &os, const Matrix &matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            os << roundToZero(matrix.m[i][j]) << " ";
        }
        os << endl;
    }
    return os;
}

ostream &operator<<(ostream &os, const Point &p) {
    os << "[ " << roundToZero(p.e[0]) << ' ' 
              << roundToZero(p.e[1]) << ' ' 
              << roundToZero(p.e[2]) << " ]" << endl;
    return os;
}

int main() {
    Point p(1, 1, 1);

    Matrix translation = Matrix::translate(2, 3, 4);
    Point pTranslated = translation * p;
    cout << "After translation: " << pTranslated;

    Matrix scaling = Matrix::scale(2, 2, 2);
    Point pScaled = scaling * p;
    cout << "After scaling: " << pScaled;

    Matrix rotationZ = Matrix::rotateZ(60);
    Point pRotatedZ = rotationZ * pTranslated;
    cout << "After rotation around Z: " << pRotatedZ;

    Matrix rotationX = Matrix::rotateX(60);
    Point pRotatedX = rotationX * pTranslated;
    cout << "After rotation around X: " << pRotatedX;
    
    Matrix rotationY = Matrix::rotateY(60);
    Point pRotatedY = rotationY * pTranslated;
    cout << "After rotation around Y: " << pRotatedY;

    return 0;
}
