#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

int printArray(const vector<int>& arrayToPrint) {
    cout << "Массив: ";
    for (int num : arrayToPrint)
        cout << num << " ";
    cout << endl;
    return 0;
}

int addToArray(vector<int>& dynamicArray, int newNumber) {
    dynamicArray.push_back(newNumber);
    return 0;
}

int removeElement(vector<int>& dynamicArray, int position) {
    if (position < 0 || position >= dynamicArray.size())
        return -1;
    dynamicArray.erase(dynamicArray.begin() + position);
    return 0;
}

int findInArray(const vector<int>& dynamicArray, int toFindNumber) {
    for (size_t i = 0; i < dynamicArray.size(); i++)
        if (dynamicArray[i] == toFindNumber)
            return i;
    return -1;
}

int findLongestIncreasingSubsequence(const vector<int>& dynamicArray, int& start, int& end) {
    int maxLength = 1;
    int currentLength = 1;
    start = end = 0;

    for (size_t i = 1; i < dynamicArray.size(); i++) {
        if (dynamicArray[i] > dynamicArray[i - 1]) {
            currentLength++;
            if (currentLength > maxLength) {
                maxLength = currentLength;
                start = i - maxLength + 1;
                end = i;
            }
        } else {
            currentLength = 1;
        }
    }
    return maxLength;
}

int insertBeforeSubsequence(vector<int>& dynamicArray, int newNumber) {
    int start, end;
    findLongestIncreasingSubsequence(dynamicArray, start, end);
    dynamicArray.insert(dynamicArray.begin() + start, newNumber);
    return 0;
}

int removeSubsequence(vector<int>& dynamicArray) {
    int start, end;
    int length = findLongestIncreasingSubsequence(dynamicArray, start, end);
    if (length == 0)
        return -1;
    dynamicArray.erase(dynamicArray.begin() + start, dynamicArray.begin() + end + 1);
    return 0;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    vector<int> dynamicArray;
    char menu;
    int tempNumber;
    int result;
    int length;
    int start, end;

    cout << "1. Вывод массива\n"
        << "2. Добавить элемент\n"
        << "3. Удалить элемент\n"
        << "4. Найти элемент\n"
        << "5. Найти индексы самой длинной упорядоченной по возрастанию подпоследовательности\n"
        << "6. Вставить новый элемент перед элементом, с начальным индексом подпоследовательности\n"
        << "7. Удалить все элементы найденной подпоследовательности\n"
        << "0. выход\n";

    while (true) {
        cout << "Выберите действие: ";
        cin >> menu;
        switch (menu) {
        case '1':
            printArray(dynamicArray);
            break;
        case '2':
            cout << "Введите число: ";
            cin >> tempNumber;
            addToArray(dynamicArray, tempNumber);
            cout << "Элемент успешно добавлен\n";
            break;
        case '3':
            cout << "Введите позицию: ";
            cin >> tempNumber;
            if (removeElement(dynamicArray, tempNumber) == -1)
                cout << "Такого элемента нет\n";
            else
                cout << "Элемент успешно удален\n";
            break;
        case '4':
            cout << "Введите число: ";
            cin >> tempNumber;
            result = findInArray(dynamicArray, tempNumber);
            if (result == -1)
                cout << "Элемент не найден\n";
            else
                cout << "Элемент " << tempNumber << " найден в позиции " << result << endl;
            break;
        case '5':
            length = findLongestIncreasingSubsequence(dynamicArray, start, end);
            if (length > 0)
                cout << "Самая длинная упорядоченная подпоследовательность: " << length << " элементов, начиная с индекса " << start << " и заканчивая индексом " << end << endl;
            else
                cout << "Упорядоченная подпоследовательность не найдена\n";
            break;
        case '6':
            cout << "Введите новый элемент: ";
            cin >> tempNumber;
            insertBeforeSubsequence(dynamicArray, tempNumber);
            cout << "Элемент успешно вставлен\n";
            break;
        case '7':
            if (removeSubsequence(dynamicArray) == -1)
                cout << "Упорядоченная подпоследовательность не найдена\n";
            else
                cout << "Упорядоченная подпоследовательность удалена\n";
            break;
        case '0':
            return 0;
        default:
            cout << "Неверный ввод!" << endl;
            break;
        }
    }

    return 0;
}
