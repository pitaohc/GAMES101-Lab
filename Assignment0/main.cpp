#include<cmath>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>
#include<iostream>

using std::cout;
using std::endl;

const float deg2rad(const float &deg) {
    return deg / 180.0 * acos(-1);
}

/**
 * Rotate the Vector by counterclockwise
 * */
const Eigen::Vector3f rotate(const Eigen::Vector3f &point, const float &degree) {
    float cosx = cos(deg2rad(degree));
    float sinx = sin(deg2rad(degree));
    Eigen::Matrix3f matrix;
    matrix << cosx, -sinx, 0,
            sinx, cosx, 0,
            0, 0, 1;
    return matrix * point;
}

/**
 * Rotate the Vector by translation
 * [x', y', z'] = [x, y, z] + [ox, oy, oz] = [x+ox, y+oy, z+oz]
 * */
const Eigen::Vector3f translation(const Eigen::Vector3f &point, const Eigen::Vector3f offset) {
    Eigen::Matrix3f matrix;
    matrix << 1, 0, offset(0),
            0, 1, offset(1),
            0, 0, 1;
    cout << "Log:\n"
         << "Matrix\n"
         << matrix << endl;
    cout << "point\n" << point << endl;
    cout << "result:\n" << matrix * point << endl;
    return matrix * point;
}

int main() {

    Eigen::Vector3f point(2.0f, 1.0f, 1.0f);
    Eigen::Vector3f result;
    cout << point << endl; //output initial point


    result = rotate(point, 45);
    cout << "Rotate\n"
         << result << endl;

    result = translation(result, Eigen::Vector3f(1.0f, 2.0f, 0.0f));
    cout << "Translation\n"
         << result << endl;

    return 0;
}