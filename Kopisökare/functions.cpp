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

//Function that prints out all the copies
void printCopy(std::vector<copyfiles> copyResults, std::vector<foundfile> results)
{
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
        getInfo(copyResults, results);

        std::cout << "Search another file?" << '\n' << "y / n" << '\n';
        std::cin >> userChoice;

        if (userChoice == "y")
        {
            continue;
        }

        if (userChoice == "n")
        {
            break;
        }

        else
        {
            std::cout << "Not a valid option!" << '\n';
            system("pause");
        }
    }
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

        if (a == 1)
        {
            getInfo(copyResults, results);
            continue;
        }

        if (a == 2)
        {
            break;
        }

        else {
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

        if (a == 1)
        {
            getInfo(copyResults, results);
            continue;
        }

        if (a == 2)
        {
            break;
        }

        else {
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

        if (a == 1)
        {
            getInfo(copyResults, results);
            continue;
        }

        if (a == 2)
        {
            break;
        }

        else {
            std::cout << "Not a valid option!" << '\n';
            system("pause");
        }
    }
}

//Function that sorts by highest amount of copies
void sortAmount(std::vector<copyfiles> copyResults, std::vector<foundfile> results)
{
    int a = 0;
    //Hittar antalet kopior och lägger till antalet i objektet
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

    //Sorterar efter antal kopior från högt till lägst
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

        if (a == 1)
        {
            getInfo(copyResults, results);
            continue;
        }

        if (a == 2)
        {
            break;
        }

        else {
            std::cout << "Not a valid option!" << '\n';
            system("pause");
        }
    }
}
