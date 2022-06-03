#pragma once
#include "include.h"


//the struct for the HumanReadable
struct HumanReadable {
    std::uintmax_t size{};

    template <typename Os> friend Os& operator<< (Os& os, HumanReadable hr)
    {
        int i{};
        double mantissa = hr.size;
        for (; mantissa >= 1024.; ++i) {
            mantissa /= 1024.;
        }
        mantissa = std::ceil(mantissa * 10.) / 10.;
        os << mantissa << "BKMGTPE"[i];
        return i == 0 ? os : os << "B (" << hr.size << ')';
    }
};

//Function that calculates total size of all copies combined
uintmax_t totalCopySize(std::vector <copyfiles> copyResults);
//Function that calculates total size of all originals combined
uintmax_t totalSize(std::vector <foundfile> results);
//Function that writes out the info about the copy objects
void getInfo(std::vector<copyfiles> copyResults, std::vector<foundfile> result);
//Function that sorts the vector alphabetically
void sortAlp(std::vector<copyfiles> copyResults, std::vector<foundfile> result);
//Function that sorts largest to smallest
void sortLargeToSmall(std::vector<copyfiles> copyResults, std::vector<foundfile> result);
//Function that sorts smallest to largest
void sortSmallToLarge(std::vector<copyfiles> copyResults, std::vector<foundfile> result);
//Function that sorts by highest amount of copies
void sortAmount(std::vector<copyfiles> copyResults, std::vector<foundfile> result);
//Catches user input of originPath
std::filesystem::path pathCatch();
//Finds all instances in originPath
std::vector <foundfile> collectAll(std::filesystem::path filePath);
//Finds all instanses of copies
std::vector <copyfiles> collectCopies(std::vector<foundfile> results);
//Runs menu text
void showMenu(std::vector<copyfiles> copyResults, std::vector<foundfile> results);