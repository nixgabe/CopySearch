#include "include.h"

int main(int argc, char* argv[])
{
    while (true)
    {
        std::filesystem::path filePath{ pathCatch() };
        if (filePath == "Bye") 
        {
            break;
        }
        std::vector <foundfile> results { collectAll(filePath) };
        std::vector <copyfiles> copyResults{ collectCopies(results) };
        showMenu(copyResults, results);        
        system("cls");
    }
}
