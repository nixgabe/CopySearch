#include "functions.h"
#include "include.h"

//Function that calculates total size of all copies
uintmax_t totalCopySize(std::vector <copyfiles> copyResults)
{
    uintmax_t sum = 0;
    for (int i = 0; i < copyResults.size(); i++) {
        sum += copyResults[i].fileSize;
    }
    return sum;
}

//Function that calculates total size of all found objects
uintmax_t totalSize(std::vector <foundfile> results)
{
    uintmax_t sum = 0;
    for (int i = 0; i < results.size(); i++) {
        sum += results[i].fileSize;
    }
    return sum;
}

//Function that writes out the info about the copy objects
void getInfo(std::vector<copyfiles> copyResults, std::vector<foundfile> results)
{
    int x = 0;
    std::cout << "Enter the number of the file you wish to see contents off." << '\n';
    while (true)
    {
        std::cin >> x;

        if (x < 0)
        {
            std::cout << "Not a valid option!" << '\n';
        }

        if (x > copyResults.size()) {
            std::cout << "Not a valid option!" << '\n';
        }

        else
        {
            x -= 1;
            string copyName = copyResults[x].fileName;
            uintmax_t copySize = copyResults[x].fileSize;
            system("cls");
            std::cout << "Filesize - " << HumanReadable{ copySize } << '\n' << '\n';
            std::cout << "Pathfiles - " << '\n' << '\n';

            for (int i = 0; i < results.size(); i++)
            {
                if (copyName == results[i].fileName &&
                    copySize == results[i].fileSize)
                {
                    std::cout << results[i].filePath << '\n';
                    std::cout << '\n';
                }
            }
            system("pause");
            break;
        }
    }

}

//Function that sorts the vector alphabetically
void sortAlp(std::vector<copyfiles> copyResults, std::vector<foundfile> results)
{
    std::sort(copyResults.begin(),
        copyResults.end(),
        [](const copyfiles& lhs, const copyfiles& rhs)
        {
            return lhs.fileName < rhs.fileName;
        });
    int a = 0;
    string userChoice;
    while (true)
    {
        system("cls");
        int x = 1;
        for (int i = 0; i < copyResults.size(); i++)
        {
            std::cout << x << ". " << copyResults[i].fileName << " has a clone." << '\n';
            x += 1;

        }

        std::cout << '\n';
        std::cout << "1. Expand on a file." << '\n';
        std::cout << "2. Return." << '\n';
        std::cin >> a;

        switch (a)
        {
        case 1:
            getInfo(copyResults, results);
            continue;

        case 2:
            return;

        default:
            std::cout << "Not a valid option!" << '\n';
            system("pause");
        }
    }
}

//Function that sorts largest to smallest
void sortLargeToSmall(std::vector<copyfiles> copyResults, std::vector<foundfile> results)
{
    system("cls");
    int a = 0;
    std::sort(copyResults.begin(),
        copyResults.end(),
        [](const copyfiles& lhs, const copyfiles& rhs)
        {
            return lhs.fileSize > rhs.fileSize;
        });

    string userChoice;
    while (true)
    {
        system("cls");
        int x = 1;
        for (int i = 0; i < copyResults.size(); i++)
        {
            std::cout << x << ". " << copyResults[i].fileName << " has a clone." << '\n';
            std::cout << "Filesize " << HumanReadable{ copyResults[i].fileSize } << '\n';
            x += 1;

        }

        std::cout << '\n';
        std::cout << "1. Expand on a file." << '\n';
        std::cout << "2. Return." << '\n';
        std::cin >> a;

        switch (a)
        {
        case 1:
            getInfo(copyResults, results);
            continue;

        case 2:
            return;

        default:
            std::cout << "Not a valid option!" << '\n';
            system("pause");
        }
    }
}

//Function that sorts smallest to largest
void sortSmallToLarge(std::vector<copyfiles> copyResults, std::vector<foundfile> results)
{
    int a = 0;
    std::sort(copyResults.begin(),
        copyResults.end(),
        [](const copyfiles& lhs, const copyfiles& rhs)
        {
            return rhs.fileSize > lhs.fileSize;
        });

    string userChoice;
    while (true)
    {
        system("cls");
        int x = 1;
        for (int i = 0; i < copyResults.size(); i++)
        {
            std::cout << x << ". " << copyResults[i].fileName << " has a clone." << '\n';
            std::cout << "Filesize " << HumanReadable{ copyResults[i].fileSize } << '\n';
            x += 1;

        }

        std::cout << '\n';
        std::cout << "1. Expand on a file." << '\n';
        std::cout << "2. Return." << '\n';
        std::cin >> a;

        switch (a)
        {
        case 1:
            getInfo(copyResults, results);
            continue;

        case 2:
            return;

        default:
            std::cout << "Not a valid option!" << '\n';
            system("pause");
        }
    }
}

//Function that sorts by highest amount of copies
void sortAmount(std::vector<copyfiles> copyResults, std::vector<foundfile> results)
{
    int a = 0;
    //Finds the amount of copies and updates the object with that info
    int hits = 0;
    for (int x = 0; x < copyResults.size(); x++)
    {
        for (int i = 0; i < results.size(); i++)
        {
            if (results[i].fileName == copyResults[x].fileName && results[i].fileSize == copyResults[x].fileSize
                && results[i].filePath != copyResults[x].filePath)
            {
                hits += 1;
            }
        }
        copyResults[x].copyAmount = hits;
        hits = 0;
    }

    //Sorts the copies from high to low
    std::sort(copyResults.begin(),
        copyResults.end(),
        [](const copyfiles& lhs, const copyfiles& rhs)
        {
            return lhs.copyAmount > rhs.copyAmount;
        });
    while (true)
    {
        system("cls");
        int i = 1;
        for (int x = 0; x < copyResults.size(); x++)
        {
            std::cout << i << ". " << copyResults[x].fileName << " has " << copyResults[x].copyAmount << " clone(s)." << '\n';
            i += 1;
        }

        std::cout << '\n';
        std::cout << "1. Expand on a file." << '\n';
        std::cout << "2. Return." << '\n';
        std::cin >> a;

        switch (a)
        {
            case 1: 
                getInfo(copyResults, results);
                continue;

            case 2:
                return;

            default:
                std::cout << "Not a valid option!" << '\n';
                system("pause");
        }
    }
}

//Functin that catches up the entered path by user and returns it
std::filesystem::path pathCatch()
{
    std::string userPath;
    std::cout << "Enter the origin path to the folder you want to check." << '\n';
    std::cout << "Enter Bye to exit." << '\n';
    std::cin >> userPath;

    //Puts string into a filepath for comp to read
    std::filesystem::path filePath(userPath);
    return filePath;
}

//Function that collects all instanses of a file and returns it in a vector
std::vector <foundfile> collectAll(std::filesystem::path filePath)
{
    string fileOrigin;
    string fileName;
    uintmax_t fileSize;
    string fileType;
    int filePosition = 0;

    std::vector <foundfile> results;

    for (auto& direntry : std::filesystem::recursive_directory_iterator::
        recursive_directory_iterator(filePath))
    {
        fileOrigin = direntry.path().string();
        fileName = direntry.path().filename().string();
        fileSize = direntry.file_size();
        fileType = std::filesystem::path(direntry).extension().string();

        if (fileType == "")
        {
            continue;
        }

        else
        {
            foundfile foundFile;
            foundFile.filePath = fileOrigin;
            foundFile.fileName = fileName;
            foundFile.fileSize = fileSize;
            foundFile.fileType = fileType;
            filePosition += 1;
            results.insert(results.end(), foundFile);
        }
    }

    return results;
}

//Function that compares to the result vector and filters out the copies
std::vector <copyfiles> collectCopies(std::vector<foundfile> results)
{
    //Loops through the saved objekts and searches for a copy
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

    return copyResults;
}

//Skriver ut menyn och alternativen
void showMenu(std::vector<copyfiles> copyResults, std::vector<foundfile> results)
{
    uintmax_t sumCopy = 0;
    uintmax_t sumTotal = 0;
    sumCopy = totalCopySize(copyResults);
    sumTotal = totalSize(results);

    while (true) {
        system("cls");
        int userChoice = 0;

        std::cout << copyResults.size() << " instances found of copies." << '\n';
        /*HumanReadable makes the file size readable for normal people and
        mentions if it's a bt or MB, etc*/
        std::cout << HumanReadable{ sumCopy } << " out of " << HumanReadable{ sumTotal } << " belongs to copyfiles."
            << '\n' << '\n';
        std::cout << "1. Sort by name." << '\n';
        std::cout << "2. Sort by most copies" << '\n';
        std::cout << "3. Sort by largest to smallest." << '\n';
        std::cout << "4. Sort by smallest to largest." << '\n' << '\n';
        std::cout << "9. Return to search." << '\n' << '\n';
        std::cin >> userChoice;

        switch (userChoice)
        {
        case 1:
            sortAlp(copyResults, results);
            continue;

        case 2:
            sortAmount(copyResults, results);
            continue;

        case 3:
            sortLargeToSmall(copyResults, results);
            continue;

        case 4: 
            sortSmallToLarge(copyResults, results);
            continue;

        case 9:
            return;

        default:
            std::cout << "Not a valid option!" << '\n';
            system("pause");
            system("cls");
        }
    }
}