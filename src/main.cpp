#include "Map.hpp"
#include "matplotlibcpp.h"
#include "utils.hpp"
#include <vector>
#include <tuple>
#include <queue>
#include <unordered_map>

namespace plt = matplotlibcpp;

int main() {
    Map mapGenerate;
    std::vector<float> map = mapGenerate.getMap();

    int xStar = mapGenerate.getXStar();
    int yStar = mapGenerate.getYStar();
    int xEnd = mapGenerate.getXEnd();
    int yEnd = mapGenerate.getYEnd();

    int i = xStar;
    int j = yStar;
    int cost = 0;

    std::vector<std::pair<int, int>> visited;
    visited.push_back(std::make_pair(i, j));

    // 优先队列
    std::priority_queue<IJWithCost, std::vector<IJWithCost>, IJWithCostComparator> queue;

    // 初始化优先队列
    queue.push(IJWithCost{i, j, cost});

    // 存储父节点信息
    // std::unordered_map<std::pair<int, int>, std::pair<int, int>> parent_map;

    // 开始迭代
    while (!queue.empty()) {
        // 取出优先队列中的第一个元素
        auto current = queue.top();
        queue.pop();

        i = current.ij.first;
        j = current.ij.second;
        cost = current.cost;

        // 如果当前节点是终点，则停止迭代
        if (i == xEnd && j == yEnd) {
            break;
        }

        // 遍历当前节点的邻居
        IterIj(i, j, mapGenerate, map, cost, visited, queue);

        // 显示当前地图状态
        plt::imshow(map.data(), 50, 50, 3, {{"interpolation", "nearest"}});
        plt::show();
    }

    // 最终显示地图
    plt::imshow(map.data(), 50, 50, 3, {{"interpolation", "nearest"}});
    plt::show();

    return 0;
}