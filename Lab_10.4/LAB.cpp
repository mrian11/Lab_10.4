#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

void Create(const char* fName);
void Print(const char* fName);
void ReverseAndRemove(const char* fname, char excludedChar);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char fname[100];
    int menuItem;

    do {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - Створення файлу" << endl;
        cout << " [2] - Вивід даних на екран" << endl;
        cout << " [3] - Перепис файлу" << endl;
        cout << " [0] - вихід" << endl;

        cout << "Введіть значення: ";
        cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem)
        {
        case 1:
            cin.ignore();
            cout << "Введіть ім'я файлу: ";
            cin.getline(fname, 99);
            Create(fname);
            break;
        case 2:
            Print(fname);
            break;
        case 3:
            cin.ignore();
            cout << "Введіть ім'я файлу для перепису: ";
            cin.getline(fname, 99);
            char excludedChar;
            cout << "Введіть символ для виключення: ";
            cin >> excludedChar;
            ReverseAndRemove(fname, excludedChar);
            Print(fname);
            break;
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    return 0;
}

void Create(const char* fName)
{
    ofstream f(fName);
    string s;
    char c;
    do
    {
        cout << "Введіть вміст файлу: ";
        getline(cin, s);
        f << s << endl;
        cout << "Продовжити? (y/n): ";
        cin >> c;
    } while (c == 'y' || c == 'Y');
}

void Print(const char* fName)
{
    cout << endl << "\nFile \"" << fName << "\":\n";
    ifstream f(fName);
    string line;
    while (getline(f, line))
    {
        cout << line << endl;
    }
    cout << endl;
}
void ReverseAndRemove(const char* fname, char excludedChar)
{
    ifstream inputFile(fname);
    ofstream outputFile("TMP.TXT");

    if (!inputFile.is_open())
    {
        cerr << "Неможливо відкрити файл " << fname << endl;
        return;
    }

    if (!outputFile.is_open())
    {
        cerr << "Неможливо відкрити вихідний файл: TMP.TXT" << endl;
        inputFile.close();
        return;
    }

    string line;
    while (getline(inputFile, line))
    {
    
        line.erase(remove(line.begin(), line.end(), excludedChar), line.end());

        reverse(line.begin(), line.end());

        outputFile << line << endl;
    }

    inputFile.close();
    outputFile.close();

    ifstream tempFile("TMP.TXT");
    if (!tempFile.is_open())
    {
        cerr << "Неможливо відкрити тимчасовий файл" << endl;
        return;
    }

    ofstream finalOutput(fname);
    if (!finalOutput.is_open())
    {
        cerr << "Неможливо відкрити файл: " << fname << endl;
        tempFile.close();
        return;
    }

    string content;
    while (getline(tempFile, line))
    {
        content = line + "\n" + content;  
    }

    finalOutput << content;

    cout << "Вміст файлу вивернуто та скопійовано (з виключенням символу '" << excludedChar << "') успішно." << endl;

    tempFile.close();
    finalOutput.close();
    std::remove("TMP.TXT");
}