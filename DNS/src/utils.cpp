#include "utils.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;
// 打开 JSON 文件
json readJsonFile(std::string filePath){
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open the JSON file." << std::endl;
        return 1;
    }
    // 从文件流中读取 JSON 数据
    json jsonData;
    file >> jsonData;
    return jsonData;
}