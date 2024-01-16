#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;
json readJsonFile(std::string filePath);