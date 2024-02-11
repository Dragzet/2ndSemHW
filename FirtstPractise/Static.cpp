#include <iostream>
#include <Windows.h>

using namespace std;

const int maxStaticSize = 5;

int printArray(int arrayToPrint[], int size) {
    cout << "Массив: ";
    for (int i = 0; i < size; i++)
        cout << arrayToPrint[i] << " ";
    cout << endl;
    return 0;
}

int addToArray(int staticArray[], int& size, int newNumber) {
    if (size >= maxStaticSize) return -1;
    staticArray[size] = newNumber;
    size++;
    return 0;
}

int RemoveFromArray(int staticArray[], int& size, int position) {
    if (size <= 0) return -1;
    if (position >= size) return -2;
    for (int i = position; i < size - 1; i++)
        staticArray[i] = staticArray[i + 1];
    size--;
    return 0;
}

int findInArray(int staticArray[], int& size, int toFindNumber) {
    for (int i = 0; i < size; i++)
        if (staticArray[i] == toFindNumber)
            return i;
    return -1;
}

int findLongestIncreasingSubsequence(int staticArray[], int size, int& start, int& end) {
    int maxLength = 1;
    int currentLength = 1;
    start = end = 0;

    for (int i = 1; i < size; i++) {
        if (staticArray[i] > staticArray[i - 1]) {
            currentLength++;
            if (currentLength > maxLength) {
                maxLength = currentLength;
                start = i - maxLength + 1;
                end = i;
            }
        }
        else {
            currentLength = 1;
        }
    }
    return maxLength;
}

int insertBeforeSubsequence(int staticArray[], int& size, int newNumber) {
    if (size >= maxStaticSize) return -1;
    int start, end;
    findLongestIncreasingSubsequence(staticArray, size, start, end);
    for (int i = size; i > start; i--)
        staticArray[i] = staticArray[i - 1];
    staticArray[start] = newNumber;
    size++;
    return 0;
}

int removeSubsequence(int staticArray[], int& size, int start, int end) {
    if (size <= 0) return -1;
    for (int i = start; i <= end; i++) {
        for (int j = start; j < size - 1; j++)
            staticArray[j] = staticArray[j + 1];
        size--;
    }
    return 0;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int currentStaticSize = 0;
    int staticArray[maxStaticSize];
    int tempNumber;
    int result;

    cout << "1. Вывод массива\n"
        << "2. Добавить элемент\n"
        << "3. Удалить элемент\n"
        << "4. Найти элемент\n"
        << "5. Найти индексы самой длинной упорядоченной по возрастанию подпоследовательности\n"
        << "6. Вставить новый элемент перед элементом, с начальным индексом подпоследовательности\n"
        << "7. Удалить все элементы найденной подпоследовательности\n"
        << "0. выход\n";

    char menu;
    while (true) {
        cout << "Выберите действие: ";
        cin >> menu;
        switch (menu) {
        case '1':
            printArray(staticArray, currentStaticSize);
            break;
        case '2':
            cout << "Введите число: ";
            cin >> tempNumber;
            if (addToArray(staticArray, currentStaticSize, tempNumber) == -1) cout << "Массив полон\n";
            else cout << "Элемент успешно добавлен\n";
            break;
        case '3':
            cout << "Введите позицию: ";
            cin >> tempNumber;
            switch (RemoveFromArray(staticArray, currentStaticSize, tempNumber)) {
            case 0:
                cout << "Элемент успешно удален\n";
                break;
            case -1:
                cout << "Массив пуст\n";
                break;
            case -2:
                cout << "Такого элемента нет\n";
                break;
            }
            break;
        case '4':
            cout << "Введите число: ";
            cin >> tempNumber;
            result = findInArray(staticArray, currentStaticSize, tempNumber);
            if (result == -1) cout << "Элемент не найден\n";
            else printf("Элемент {:d} найден в позиции {:d}\n", tempNumber, result);
            break;
        case '5':
            int start, end;
            result = findLongestIncreasingSubsequence(staticArray, currentStaticSize, start, end);
            cout << "Самая длинная упорядоченная подпоследовательность: " << result << " элементов, начиная с индекса " << start << " и заканчивая индексом " << end << endl;
            break;
        case '6':
            cout << "Введите новый элемент: ";
            cin >> tempNumber;
            if (insertBeforeSubsequence(staticArray, currentStaticSize, tempNumber) == -1)
                cout << "Массив полон\n";
            else
                cout << "Элемент успешно вставлен\n";
            break;
        case '7':
            result = findLongestIncreasingSubsequence(staticArray, currentStaticSize, start, end);
            if (result > 0) {
                removeSubsequence(staticArray, currentStaticSize, start, end);
                cout << "Подпоследовательность удалена\n";
            }
            else
                cout << "Подпоследовательность не найдена\n";
            break;
        case '0':
            return 0;
        default:
            cout << "Неверный ввод!";
            cout << "1. Вывод массива\n"
                << "2. Добавить элемент\n"
                << "3. Удалить элемент\n"
                << "4. Найти\n"
                << "5. Найти индексы самой длинной упорядоченной по возрастанию подпоследовательности\n"
                << "6. Вставить новый элемент перед элементом, с начальным индексом подпоследовательности\n"
                << "7. Удалить все элементы найденной подпоследовательности\n"
                << "0. выход\n"
                << "Выберите действие: ";
            break;
        }
    }

}
