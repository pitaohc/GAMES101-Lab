#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;


const float deg2rad(const float &deg);

const Eigen::Matrix4f rotate(float angle);

const Eigen::Matrix4f translate(const Eigen::Vector3f &orientation);

const Eigen::Matrix4f scale(const Eigen::Vector3f &percentage);

/**
 * 得到视角变换矩阵
 * @param eye_pos 摄像机位置向量
 * @return 视角变换矩阵
 * */
Eigen::Matrix4f get_view_matrix(const Eigen::Vector3f &eye_pos) {
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    view = translate(-eye_pos) * view;

    return view;
}

/**
 * 获得模型变换矩阵
 * 当前任务中，只会进行旋转
 * @param rotation_angle 旋转角度
 * @return 模型变换矩阵
 * */
Eigen::Matrix4f get_model_matrix(float rotation_angle) {
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.
    model = rotate(rotation_angle);
    return model;
}


/**
 * 获得投影变换矩阵
 * @param eye_fov 视角fov
 * @param aspect_ratio 视野宽高比
 * @param zNear 视锥近平面
 * @param zFar 视锥远平面
 * @return 投影变换矩阵
 * */
Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar) {
    // Students will implement this function

    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();
    // Create the projection matrix for the given parameters.
    // Then return it.
    //1. 计算宽高
    float height = 2 * zNear * tan(deg2rad(eye_fov / 2)), width = height * aspect_ratio;

    //2. 透视投影
    projection << zNear, 0, 0, 0,
            0, zNear, 0, 0,
            0, 0, zNear + zFar, -zNear * zFar,
            0, 0, 1, 0;

    //3. 正交投影
    Eigen::Matrix4f my_scale = scale({-1 / width, -1 / height, 1 / (zFar - zNear)});
    Eigen::Matrix4f my_translate = translate({0, 0, zNear + (zFar - zNear) / 2});

    return my_scale * my_translate * projection;
//    // Students will implement this function
//
//    //实际视角方向为Z轴负方向，因此zNear和zFar实际应为负数
//    zNear = -zNear;
//    zFar = -zFar;
//
//    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();
//    // Create the projection matrix for the given parameters.
//    // Then return it.
//    //1. 计算宽高
//    float top = abs(zNear) * tan(deg2rad(eye_fov / 2)), right = top * aspect_ratio;
//    std::cout << "top:" << top << ", right:" << right << std::endl;
//    //2. 透视投影
//    projection << zNear / right, 0, 0, 0,
//            0, zNear / top, 0, 0,
//            0, 0, (zNear + zFar) / (zNear - zFar), (2 * zNear * zFar) / (zFar - zNear),
//            0, 0, 1, 0;
//
//    //3. 正交投影
////    Eigen::Matrix4f my_scale = scale({-1 / width, -1 / height, 1 / (zFar - zNear)});
////    Eigen::Matrix4f my_translate = translate({0, 0, zNear + (zFar - zNear) / 2});
//
//    return projection;
}

int main(int argc, const char **argv) {
    float angle = 0; //旋转角度
    bool command_line = false; //是否有命令行
    std::string filename = "output.png"; //保存图片名称

    //read argument ./rasterizer -r {angle} {filename}
    if (argc >= 3) {
        command_line = true;
        angle = std::stof(argv[2]); // -r by default
        if (argc == 4) {
            filename = std::string(argv[3]);
        }
    }
    std::cout << "Argument angle: " << angle << std::endl;
    std::cout << "Argument filename: " << filename << std::endl;

    //Set the view width and height
    rst::rasterizer r(700, 700);

    //Set the viewport position
    Eigen::Vector3f eye_pos = {0, 0, 5};

    //Set the triangle position
    std::vector<Eigen::Vector3f> pos{{2,  0, -2},
                                     {0,  2, -2},
                                     {-2, 0, -2}};
    //Bing the point with index
    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

    //load triangle
    auto pos_id = r.load_positions(pos); //handle of position
    auto ind_id = r.load_indices(ind); //handle of index

    int key = 0; //接受键盘输入
    int frame_count = 0;// statistics frame count
    /* if we input command with arguments, the program will generate a picture then return. */
    if (command_line) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));
        std::cout << "projection matrix: " << get_projection_matrix(45, 1, 0.1, 50) << std::endl;
        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);

        cv::imwrite(filename, image);

        return 0;
    }

    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth); //清除帧缓冲区和深度缓冲区
        std::cout << "angle: " << angle << std::endl;
//        std::cout << "model transform:\n" << get_model_matrix(angle) << std::endl;
        //设置MVP变换矩阵
        r.set_model(get_model_matrix(angle)); //model transform
        r.set_view(get_view_matrix(eye_pos));   //view transform
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));//projection transform

        //draw triangle to frame buffer
        r.draw(pos_id, ind_id, rst::Primitive::Triangle);

        //read frame buffer
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);
        key = cv::waitKey(10);

        std::cout << "frame count: " << frame_count++ << '\n';

        if (key == 'a') {
            angle += 10;
        } else if (key == 'd') {
            angle -= 10;
        }
    }

    return 0;
}

/**
 * 角度转换成弧度
 * */
const float deg2rad(const float &deg) {
    return (float) (deg / 180.0 * acos(-1));
}

/**
 * 旋转指定角度
 * */
const Eigen::Matrix4f rotate(float angle) {
    Eigen::Matrix4f matrix;
    float cosx = cos(deg2rad(angle));
    float sinx = sin(deg2rad(angle));
    matrix << cosx, -sinx, 0, 0,
            sinx, cosx, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1;
    return matrix;
}

/**
 * 缩放三个轴到指定大小
 * */
const Eigen::Matrix4f scale(const Vector3f &percentage) {
    Eigen::Matrix4f result;
    result << percentage[0], 0, 0, 0,
            0, percentage[1], 0, 0,
            0, 0, percentage[2], 0,
            0, 0, 0, 1;
    return result;
}

/**
 * 平移对象
 * @param orientation 方向向量
 * */
const Eigen::Matrix4f translate(const Vector3f &orientation) {
    Eigen::Matrix4f result;
    result << 1, 0, 0, orientation[0],
            0, 1, 0, orientation[1],
            0, 0, 1, orientation[2],
            0, 0, 0, 1;
    return result;
}
