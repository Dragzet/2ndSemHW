#include <iostream>
#include <Windows.h>

using namespace std;

int printArray(int* arrayToPrint, int size) {
    cout << "Массив: ";
    for (int i = 0; i < size; i++)
        cout << arrayToPrint[i] << " ";
    cout << endl;
    return 0;
}

int addToArray(int*& dynamicArray, int& size, int newNumber) {
    int* newArray = new int[size + 1];
    for (int i = 0; i < size; ++i)
        newArray[i] = dynamicArray[i];
    newArray[size++] = newNumber;
    delete[] dynamicArray;
    dynamicArray = newArray;
    return 0;
}

int removeElement(int*& dynamicArray, int& size, int position) {
    if (position < 0 || position >= size)
        return -1;
    for (int i = position; i < size - 1; ++i)
        dynamicArray[i] = dynamicArray[i + 1];
    --size;
    int* newArray = new int[size];
    for (int i = 0; i < size; ++i)
        newArray[i] = dynamicArray[i];
    delete[] dynamicArray;
    dynamicArray = newArray;
    return 0;
}

int findInArray(int* dynamicArray, int size, int toFindNumber) {
    for (int i = 0; i < size; i++)
        if (dynamicArray[i] == toFindNumber)
            return i;
    return -1;
}

int findLongestIncreasingSubsequence(int* dynamicArray, int size, int& start, int& end) {
    int maxLength = 1;
    int currentLength = 1;
    start = end = 0;

    for (int i = 1; i < size; i++) {
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

int insertBeforeSubsequence(int*& dynamicArray, int& size, int newNumber) {
    int start, end;
    findLongestIncreasingSubsequence(dynamicArray, size, start, end);
    int* newArray = new int[size + 1];
    int j = 0;
    for (int i = 0; i < size + 1; ++i) {
        if (i == start) {
            newArray[i] = newNumber;
        } else {
            newArray[i] = dynamicArray[j++];
        }
    }
    delete[] dynamicArray;
    dynamicArray = newArray;
    size++;
    return 0;
}

int removeSubsequence(int*& dynamicArray, int& size) {
    int start, end;
    int length = findLongestIncreasingSubsequence(dynamicArray, size, start, end);
    if (length == 0)
        return -1;
    int newSize = size - (end - start + 1);
    int* newArray = new int[newSize];
    int j = 0;
    for (int i = 0; i < size; ++i) {
        if (i < start || i > end) {
            newArray[j++] = dynamicArray[i];
        }
    }
    delete[] dynamicArray;
    dynamicArray = newArray;
    size = newSize;
    return 0;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int* dynamicArray = nullptr;
    int currentDynamicSize = 0;
    int tempNumber;
    char menu;
    int result; 
    int length; 

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
            printArray(dynamicArray, currentDynamicSize);
            break;
        case '2':
            cout << "Введите число: ";
            cin >> tempNumber;
            addToArray(dynamicArray, currentDynamicSize, tempNumber);
            cout << "Элемент успешно добавлен\n";
            break;
        case '3':
            cout << "Введите позицию: ";
            cin >> tempNumber;
            if (removeElement(dynamicArray, currentDynamicSize, tempNumber) == -1)
                cout << "Такого элемента нет\n";
            else
                cout << "Элемент успешно удален\n";
            break;
        case '4':
            cout << "Введите число: ";
            cin >> tempNumber;
            result = findInArray(dynamicArray, currentDynamicSize, tempNumber); 
            if (result == -1)
                cout << "Элемент не найден\n";
            else
                cout << "Элемент " << tempNumber << " найден в позиции " << result << endl;
            break;
        case '5':
            length = findLongestIncreasingSubsequence(dynamicArray, currentDynamicSize, result, tempNumber);
            if (length > 0)
                cout << "Самая длинная упорядоченная подпоследовательность: " << length << " элементов, начиная с индекса " << result << " и заканчивая индексом " << tempNumber << endl;
            else
                cout << "Упорядоченная подпоследовательность не найдена\n";
            break;
        case '6':
            cout << "Введите новый элемент: ";
            cin >> tempNumber;
            insertBeforeSubsequence(dynamicArray, currentDynamicSize, tempNumber);
            cout << "Элемент успешно вставлен\n";
            break;
        case '7':
            if (removeSubsequence(dynamicArray, currentDynamicSize) == -1)
                cout << "Упорядоченная подпоследовательность не найдена\n";
            else
                cout << "Упорядоченная подпоследовательность удалена\n";
            break;
        case '0':
            delete[] dynamicArray; 
            return 0;
        default:
            cout << "Неверный ввод!" << endl;
            break;
        }
    }

    return 0;
}
