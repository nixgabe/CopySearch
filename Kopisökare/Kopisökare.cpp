#include "include.h"

int main(int argc, char* argv[])
{
    while (true)
    {
        //Basic. Creates string to later catch user input
        std::string userPath;
        std::cout << "Enter the origin path to the folder you want to check." << '\n';
        std::cout << "Enter Bye to exit." << '\n';
        std::cin >> userPath;

        if (userPath == "Bye") {
            break;
        }

        //Puts string into a filepath for comp to read
        std::filesystem::path filePath(userPath);

        /*Creates an object of the saved files with the needed info. 
        * Puts the objects into a list with the help of a for loop.*/
        string fileOrigin;
        string fileName;
        uintmax_t fileSize;
        string fileType;
        int filePosition = 0;

        std::vector <foundfile> results;

        for (auto& direntry : std::filesystem::recursive_directory_iterator::
            recursive_directory_iterator(userPath))
        {
            fileOrigin = direntry.path().string();
            fileName = direntry.path().filename().string();
            fileSize = direntry.file_size();
            fileType = std::filesystem::path(direntry).extension().string();


            foundfile foundFile;
            foundFile.filePath = fileOrigin;
            foundFile.fileName = fileName;
            foundFile.fileSize = fileSize;
            foundFile.fileType = fileType;
            filePosition += 1;
            results.insert(results.end(), foundFile);
        }

        //Loopar igenom de sparade objekt och letar kopia
        string copyOrigin;
        string copyName;
        string copyType;
        uintmax_t copySize;

        std::vector <copyfiles> copyResults;

        //This loop catches an item, which it compares to the rest of 
        // the vector in search for copies matching in fileName and fileSize.
        for (int i = 0; i < results.size(); i++)
        {
            copyOrigin = results[i].filePath;
            copyName = results[i].fileName;
            copySize = results[i].fileSize;
            copyType = results[i].fileType;

            for (int x = i + 1; x < results.size(); x++)
            {
                if (copyName == results[x].fileName && copySize == results[x].fileSize)
                {
                    copyfiles copyFile;
                    copyFile.filePath = copyOrigin;
                    copyFile.fileName = copyName;
                    copyFile.fileSize = copySize;
                    copyFile.fileType = copyType;

                    copyResults.insert(copyResults.end(), copyFile);
                    break;
                }
            }
        }

        uintmax_t sumCopy = 0;
        uintmax_t sumTotal = 0;
        sumCopy = totalCopySize(copyResults);
        sumTotal = totalSize(results);

        //Sorts the copyResults vector to be alphabethically
        std::sort(copyResults.begin(), copyResults.end(),
            [](const copyfiles& lhs, const copyfiles& rhs)
            {
                return lhs.fileName < rhs.fileName;
            });

        /*This erases the several copies in the list, so each object is only mentioned
        once despite being found multiple times in the original*/
        copyResults.erase(std::unique(copyResults.begin(), copyResults.end(),
            [](const copyfiles& lhs, const copyfiles& rhs)
            {
                return lhs.fileName == rhs.fileName;
            }), copyResults.end());

        while (true) {
            system("cls");
            int userChoice = 0;

            std::cout << copyResults.size() << " instances found of copies." << '\n';
            /*HumanReadable makes the file size readable for normal peopleand
            mentions if it's a bt or MB, etc*/
            std::cout << HumanReadable{ sumCopy } << " out of " << HumanReadable{ sumTotal } << " belongs to copyfiles."
                << '\n' << '\n';
            std::cout << "1. Sort by name." << '\n';
            std::cout << "2. Sort by most copies" << '\n';
            std::cout << "3. Sort by largest to smallest." << '\n';
            std::cout << "4. Sort by smallest to largest." << '\n' << '\n';
            std::cout << "9. Return to search." << '\n' << '\n';
            std::cin >> userChoice;

            if (userChoice == 1) {
                sortAlp(copyResults, results);
                continue;
            }

            if (userChoice == 2) {
                sortAmount(copyResults, results);
                continue;
            }

            if (userChoice == 3) {
                sortLargeToSmall(copyResults, results);
                continue;
            }

            if (userChoice == 4) {
                sortSmallToLarge(copyResults, results);
                continue;
            }

            if (userChoice == 9) {
                break;
            }

            else {
                std::cout << "Not a valid option!" << '\n';
                system("pause");
                system("cls");
            }
        }
        system("cls");
    }
}
