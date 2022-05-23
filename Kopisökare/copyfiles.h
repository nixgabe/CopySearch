#pragma once
#include <string>
using namespace std;

class copyfiles
{
    //sets structure for the copy objects
    public:
    std::string filePath;
    std::string fileName;
    uintmax_t fileSize;
    std::string fileType;
    int copyAmount;
};

