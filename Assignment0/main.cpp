#include<cmath>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>
#include<iostream>
using std::cout;
using std::endl;
int main(){

    // Basic Example of cpp
    cout << "Example of cpp \n";
    float a = 1.0, b = 2.0;
    cout << a << endl;              //1
    cout << a/b << endl;            //0.5
    cout << std::sqrt(b) << endl;   //1.4
    cout << std::acos(-1) << endl;  //π 3.14
    cout << std::sin(30.0/180.0*acos(-1)) << endl; //sin(π/6)
    cout << endl;
    // Example of vector
    cout << "Example of vector \n";
    // vector definition
    
    Eigen::Vector3f v(1.0f,2.0f,3.0f); //三维浮点向量
    Eigen::Vector3f w(1.0f,0.0f,0.0f);
    // vector output 输出向量
    cout << "Example of output \n";
    cout << v << endl;
    // vector add
    cout << "Example of add \n";
    cout << v + w << endl;
    // vector scalar multiply
    cout << "Example of scalar multiply \n";
    cout << v * 3.0f << endl; //交换律
    cout << 2.0f * v << endl;

    // Example of matrix
    cout << "Example of matrix \n";
    // matrix definition
    Eigen::Matrix3f i,j;
    i << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
    j << 2.0, 3.0, 1.0, 4.0, 6.0, 5.0, 9.0, 7.0, 8.0;
    // matrix output
    cout << "Example of output \n";
    cout << i << endl;
    // matrix add i + j
    cout << i + j << endl;
    // matrix scalar multiply i * 2.0
    cout << 2.0 * i << endl;
    cout << i * 2.0 << endl;
    // matrix multiply i * j
    cout << i * j << endl;
    // matrix multiply vector i * v
    cout << i * v << endl;

    Eigen::MatrixXd matrix_a(2,3); //2行3列的矩阵
    matrix_a << 1, 2, 3, 4, 5, 6;
    cout << matrix_a << endl;
    return 0;
}