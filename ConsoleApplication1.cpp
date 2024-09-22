// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;
std::vector<std::string> jpg;

std::vector<std::string> split(const std::string& text, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(text);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s [imagepath]\n", argv[0]);
        return -1;
    }
    std::string path = argv[1]; // 指定文件夹路径

    try {
        if (fs::exists(path) && fs::is_directory(path)) {
            for (const auto& entry : fs::directory_iterator(path)) {
                if (fs::is_regular_file(entry.status())) {
                    std::string tp = entry.path().string();
                    if (tp.find(".json")!= std::string::npos)
                    {
                        jpg.push_back(tp);
                        std::cout << tp << std::endl;
                    }
                }
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << e.what() << std::endl;
    }

    for (auto& ipath : jpg)
    {
        std::ifstream file(ipath.c_str()); // 打开文件用于读取
        std::string content;
        std::string search_for = "  \"imageHeight\": 640,\n  \"imageWidth\": 640"; // 待替换的字符串
        std::string replace_with = "  \"imageHeight\": 352,\n  \"imageWidth\": 352"; // 新的字符串

        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf(); // 读取文件内容到stringstream
            file.close(); // 关闭文件流
            content = buffer.str(); // 转换为string

            // 在content中查找并替换字符串
            std::size_t start_pos = 0;
            while ((start_pos = content.find(search_for, start_pos)) != std::string::npos) {
                content.replace(start_pos, search_for.length(), replace_with);
                start_pos += replace_with.length();
            }

            std::ofstream outfile(ipath.c_str()); // 打开文件用于写入
            outfile << content; // 写入内容
            outfile.close(); // 关闭文件流
        }
        else {
            std::cerr << "Unable to open file";
            return 1;
        }
    }
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
