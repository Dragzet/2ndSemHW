#include <iostream>
#include <windows.h>

using namespace std;

int printArray(int* arrayToPrint, int size) {
    cout << "Массив: ";
    for (int i = 0; i < size; i++)
        cout << arrayToPrint[i] << " ";
    cout << endl;
    return 0;
}

int addToArray(int*& dynamicArray, int& size, int newNumber) {
    dynamicArray = (int*)realloc(dynamicArray, (size + 1) * sizeof(int));
   
    dynamicArray[size++] = newNumber;
    return 0;
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
    dynamicArray = (int*)realloc(dynamicArray, (size + 1) * sizeof(int));
    
    for (int i = size; i > start; --i)
        dynamicArray[i] = dynamicArray[i - 1];
    dynamicArray[start] = newNumber;
    ++size;
    return 0;
}

int removeSubsequence(int*& dynamicArray, int& size) {
    int start, end;
    int length = findLongestIncreasingSubsequence(dynamicArray, size, start, end);
    if (length == 0)
        return -1;
    for (int i = start; i <= end; ++i)
        dynamicArray[i] = dynamicArray[i + end - start + 1];
    dynamicArray = (int*)realloc(dynamicArray, (size - (end - start + 1)) * sizeof(int));
    
    size -= (end - start + 1);
    return 0;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int* dynamicArray = {};
    int currentDynamicSize = 0;
    int tempNumber;
    char menu;
    int result; 
    int length; 

    cout << "1. Вывод массива\n"
        << "2. Добавить элемент\n"
        << "3. Найти индексы самой длинной упорядоченной по возрастанию подпоследовательности\n"
        << "4. Вставить новый элемент перед элементом, с начальным индексом подпоследовательности\n"
        << "5. Удалить все элементы найденной подпоследовательности\n"
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
            if (addToArray(dynamicArray, currentDynamicSize, tempNumber) == -1)
                cout << "Ошибка при добавлении элемента\n";
            else
                cout << "Элемент успешно добавлен\n";
            break;
        case '3':
            length = findLongestIncreasingSubsequence(dynamicArray, currentDynamicSize, result, tempNumber);
            if (length > 0)
                cout << "Самая длинная упорядоченная подпоследовательность: " << length << " элементов, начиная с индекса " << result << " и заканчивая индексом " << tempNumber << endl;
            else
                cout << "Упорядоченная подпоследовательность не найдена\n";
            break;
        case '4':
            cout << "Введите новый элемент: ";
            cin >> tempNumber;
            insertBeforeSubsequence(dynamicArray, currentDynamicSize, tempNumber);
            cout << "Элемент успешно вставлен\n";
            break;
        case '5':
            if (removeSubsequence(dynamicArray, currentDynamicSize) == -1)
                cout << "Упорядоченная подпоследовательность не найдена\n";
            else
                cout << "Упорядоченная подпоследовательность удалена\n";
            break;
        case '0':; 
            return 0;
        default:
           cout << "Неверный ввод!\n"
                << "1. Вывод массива\n"
                << "2. Добавить элемент\n"
                << "3. Найти индексы самой длинной упорядоченной по возрастанию подпоследовательности\n"
                << "4. Вставить новый элемент перед элементом, с начальным индексом подпоследовательности\n"
                << "5. Удалить все элементы найденной подпоследовательности\n"
                << "0. выход\n";
            break;
        }
    }

    return 0;
}
