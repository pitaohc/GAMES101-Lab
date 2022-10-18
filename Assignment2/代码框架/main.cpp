// clang-format off
#include <iostream>
#include <opencv2/opencv.hpp>
#include "rasterizer.hpp"
#include "global.hpp"
#include "Triangle.hpp"

constexpr double MY_PI = 3.1415926;

const float deg2rad(const float& deg);

const Eigen::Matrix4f rotate(float angle);

const Eigen::Matrix4f translate(const Eigen::Vector3f& orientation);

const Eigen::Matrix4f scale(const Eigen::Vector3f& percentage);

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate;
    translate << 1,0,0,-eye_pos[0],
                 0,1,0,-eye_pos[1],
                 0,0,1,-eye_pos[2],
                 0,0,0,1;

    view = translate*view;

    return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
    return model;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio, float zNear, float zFar)
{
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
    Eigen::Matrix4f my_scale = scale({ -1 / width, -1 / height, 1 / (zFar - zNear) });
    Eigen::Matrix4f my_translate = translate({ 0, 0, zNear + (zFar - zNear) / 2 });

    return my_scale * my_translate * projection;
}

int main(int argc, const char** argv)
{
    float angle = 0;
    bool command_line = false;
    std::string filename = "output.png";

    if (argc == 2)
    {
        command_line = true;
        filename = std::string(argv[1]);
    }

    rst::rasterizer r(700, 700);

    Eigen::Vector3f eye_pos = {0,0,5};


    std::vector<Eigen::Vector3f> pos
            {
                    {2, 0, -2},
                    {0, 2, -2},
                    {-2, 0, -2},
                    {3.5, -1, -5},
                    {2.5, 1.5, -5},
                    {-1, 0.5, -5}
            };

    std::vector<Eigen::Vector3i> ind
            {
                    {0, 1, 2},
                    {3, 4, 5}
            };

    std::vector<Eigen::Vector3f> cols
            {
                    {217.0, 238.0, 185.0},
                    {217.0, 238.0, 185.0},
                    {217.0, 238.0, 185.0},
                    {185.0, 217.0, 238.0},
                    {185.0, 217.0, 238.0},
                    {185.0, 217.0, 238.0}
            };

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);
    auto col_id = r.load_colors(cols);

    int key = 0;
    int frame_count = 0;

    if (command_line)
    {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, col_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);

        cv::imwrite(filename, image);

        return 0;
    }

    while(key != 27)
    {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, col_id, rst::Primitive::Triangle);

        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        cv::imshow("image", image);
        key = cv::waitKey(10);

        std::cout << "frame count: " << frame_count++ << '\n';
    }

    return 0;
}

/**
 * 角度转换成弧度
 * */
const float deg2rad(const float& deg) {
    return (float)(deg / 180.0 * acos(-1));
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
const Eigen::Matrix4f scale(const Vector3f& percentage) {
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
const Eigen::Matrix4f translate(const Vector3f& orientation) {
    Eigen::Matrix4f result;
    result << 1, 0, 0, orientation[0],
        0, 1, 0, orientation[1],
        0, 0, 1, orientation[2],
        0, 0, 0, 1;
    return result;
}

// clang-format on