#ifndef UTILS_H
#define UTILS_H
#include "Map.hpp"
#include <vector>
#include <tuple>
#include <queue>
#include <map>

bool isNotObstruction(int i, int j, const Map& mapGenerate) {
    // 传进来的可能会越界 越界返回false
    try {
        // 获取像素值
        auto pixel = mapGenerate.getPixelAt(i, j);
        
        // 如果三个通道全是0，那么返回false，表示是障碍物
        if (std::get<0>(pixel) == 0.0f && std::get<1>(pixel) == 0.0f && std::get<2>(pixel) == 0.0f) {
            return false;
        } else {
            return true;
        }
    } catch (const std::out_of_range&) {
        // 如果索引越界，也视为障碍物
        return false;
    }
}

// 检查一个坐标点是否访问过
bool isNotVisited(std::pair<int,int> ij,std::vector<std::pair<int,int>> visited)
{
    // 使用find函数查找是否访问过
    auto it = std::find(visited.begin(),visited.end(),ij);
    if (it != visited.end())
    {
        // 说明这个点存在
        // 被访问过 就不能再次访问 所以要返回false
        return false;
    }else{
        return true;
    }
}

// 创建一个结构体来封装坐标和成本
// 用于优先队列
struct IJWithCost {
    std::pair<int, int> ij;
    int cost;

    // 构造函数
    IJWithCost(int x, int y, int c) : ij(std::make_pair(x, y)), cost(c) {}

    // 重载 < 运算符 用于优先队列的比较
    bool operator<(const IJWithCost& other) const {
        return cost > other.cost; // 最小堆
    }

    // 重载 > 运算符 用于 std::greater 的比较
    bool operator>(const IJWithCost& other) const {
        return cost < other.cost; // 最大堆
    }
};

struct IJWithCostComparator {
    bool operator()(const IJWithCost& a, const IJWithCost& b) const {
        return a.cost > b.cost; // 最小堆
    }
};

void IterIj(int i, int j, Map mapGenerate, std::vector<float>& map, int cost, std::vector<std::pair<int, int>>& visited, std::priority_queue<IJWithCost, std::vector<IJWithCost>, IJWithCostComparator>& queue) {
    // 先获得地图的边界
    int xEnd = mapGenerate.getXEnd();
    int yEnd = mapGenerate.getYEnd();

    // 向下遍历
    if (i + 1 < xEnd && isNotObstruction(i + 1, j, mapGenerate) && isNotVisited(std::make_pair(i + 1, j), visited)) {
        // 如果满足条件 可以遍历
        // 记录父节点和子节点
        visited.push_back(std::make_pair(i + 1, j));
        // parent_map[std::make_pair(i + 1, j)] = std::make_pair(i, j); // 存储父节点信息
        queue.push(IJWithCost(i + 1, j, cost + 1));
        // 更新地图 该点标记为绿色
        // map[(i + 1) * yEnd + j] = 0.5f; // 例如，0.5f 表示绿色
        mapGenerate.setPixelAt(i+1,j,std::make_tuple(0,1,0));
    }

    // 向右边遍历
    if (j + 1 < yEnd && isNotObstruction(i, j + 1, mapGenerate) && isNotVisited(std::make_pair(i, j + 1), visited)) {
        visited.push_back(std::make_pair(i, j + 1));
        // parent_map[std::make_pair(i, j + 1)] = std::make_pair(i, j);
        queue.push(IJWithCost(i, j + 1, cost + 1));
        mapGenerate.setPixelAt(i,j+1,std::make_tuple(0,1,0));

    }

    // 向上遍历
    if (i - 1 >= 0 && isNotObstruction(i - 1, j, mapGenerate) && isNotVisited(std::make_pair(i - 1, j), visited)) {
        visited.push_back(std::make_pair(i - 1, j));
        // parent_map[std::make_pair(i - 1, j)] = std::make_pair(i, j);
        queue.push(IJWithCost(i - 1, j, cost + 1));
        mapGenerate.setPixelAt(i-1,j,std::make_tuple(0,1,0));

    }

    // 向左边遍历
    if (j - 1 >= 0 && isNotObstruction(i, j - 1, mapGenerate) && isNotVisited(std::make_pair(i, j - 1), visited)) {
        visited.push_back(std::make_pair(i, j - 1));
        // parent_map[std::make_pair(i, j - 1)] = std::make_pair(i, j);
        queue.push(IJWithCost(i, j - 1, cost + 1));
        mapGenerate.setPixelAt(i,j-1,std::make_tuple(0,1,0));
    }
}


#endif