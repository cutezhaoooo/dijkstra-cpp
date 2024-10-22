#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include <random>
#include <tuple>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

// 使用红色作为起点 蓝色作为终点
typedef const int Cint;

class Map
{
public:
    // 构造函数
    Map(Cint height = 50, Cint width = 50, Cint xStar = 0, Cint yStar = 0, Cint xEnd = 49, Cint yEnd = 49)
        : height(height), width(width), xStar(xStar), yStar(yStar), xEnd(xEnd), yEnd(yEnd)
    {
        // 初始化地图数据
        mapData = generateMap();
    }

    // 返回i j处的像素值
    std::tuple<float, float, float> getPixelAt(int i, int j) const
    {
        if (i < 0 || i >= height || j < 0 || j >= width) {
            throw std::out_of_range("Index out of range");
        }

        int index = (i * width + j) * 3;
        return { mapData[index], mapData[index + 1], mapData[index + 2] };
    }

    // 设置i j处的像素点的值
    void setPixelAt(int i, int j, std::tuple<float, float, float> pixel) {
        if (i < 0 || i >= height || j < 0 || j >= width) {
            throw std::out_of_range("Index out of range");
        }

        int index = (i * width + j) * 3;
        mapData[index] = std::get<0>(pixel);     // 红色通道
        mapData[index + 1] = std::get<1>(pixel); // 绿色通道
        mapData[index + 2] = std::get<2>(pixel); // 蓝色通道
    }

    // 获取地图数据
    std::vector<float> getMap() const
    {
        return mapData;
    }

    inline int getXStar()
    {
        return xStar;
    }

    inline int getYStar()
    {
        return yStar;
    }

    inline int getXEnd()
    {
        return xEnd;
    }

        inline int getYEnd()
    {
        return yEnd;
    }



private:
    Cint height;  // 地图高度
    Cint width;   // 地图宽度
    Cint xStar;   // 起点 X 坐标
    Cint yStar;   // 起点 Y 坐标
    Cint xEnd;    // 终点 X 坐标
    Cint yEnd;    // 终点 Y 坐标
    std::vector<float> mapData;  // 存储地图数据

    // 生成随机浮点数
    double random_float()
    {
        static std::default_random_engine generator;
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        return distribution(generator);
    }

    // 生成地图
    std::vector<float> generateMap()
    {
        // 创建一个三维数组来存储图像数据
        std::vector<std::vector<std::vector<double>>> image(height, std::vector<std::vector<double>>(width, std::vector<double>(3, 0.0)));

        // 填充随机颜色
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                // 得到随机值
                double val = random_float();
                if (val <= 0.25)
                {
                    // 将 val 设置为障碍物
                    val = 0.0;
                }
                else
                {
                    val = 1.0;  // 将 255 转换为 1.0
                }
                image[y][x][0] = val;  // 红色通道
                image[y][x][1] = val;  // 绿色通道
                image[y][x][2] = val;  // 蓝色通道
            }
        }

        // 将图像数据转换为适合 matplotlib 的格式
        std::vector<float> image_data(width * height * 3);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int c = 0; c < 3; ++c) {
                    image_data[(y * width + x) * 3 + c] = static_cast<float>(image[y][x][c]);
                }
            }
        }

        // 设置起点和终点
        setStartAndEnd(image_data);

        return image_data;
    }

    // 设置起点和终点
    void setStartAndEnd(std::vector<float>& image_data)
    {
        // 起点设置为红色
        int start_index = (yStar * width + xStar) * 3;
        image_data[start_index] = 1.0f;     // 红色通道
        image_data[start_index + 1] = 0.0f; // 绿色通道
        image_data[start_index + 2] = 0.0f; // 蓝色通道

        // 终点设置为蓝色
        int end_index = (yEnd * width + xEnd) * 3;
        image_data[end_index] = 0.0f;       // 红色通道
        image_data[end_index + 1] = 0.0f;   // 绿色通道
        image_data[end_index + 2] = 1.0f;   // 蓝色通道
    }
};

#endif // MAP_H