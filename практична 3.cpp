#include <iostream>
using namespace std;

int main() {
    const int n = 12;
    int a[n] = { 18, 30, 4, 24, 7, 13, 2, 27, 10, 1, 21, 6 };
    int expected[n] = { 1, 2, 4, 6, 7, 10, 13, 18, 21, 24, 27, 30 };

    // завдання 1. підготовка та відновлення масиву
    auto copyArray = [](const int a[], int b[], int size) {
        for (int i = 0; i < size; i++) b[i] = a[i];
        };

    cout << "Завдання 1. Початковий масив:\n";
    for (int x : a) cout << x << " ";
    cout << endl;

    // завдання 2. пошук позиції для бінарної вставки
    auto position = [](const int b[], int size, int key, int& c) {
        int left = 0, right = size;
        while (left < right) {
            int mid = (left + right) / 2;
            c++;
            if (b[mid] <= key) left = mid + 1;
            else right = mid;
        }
        return left;
        };

    int sample[5] = { 2, 5, 8, 11, 17 };
    int c = 0;
    cout << "\nЗавдання 2. Позиція числа 10: "
        << position(sample, 5, 10, c)
        << ", порівнянь: " << c << endl;

    // завдання 3. сортування бінарними вставками
    auto binarySort = [&](int b[], int size, int& c, int& m) {
        c = m = 0;
        for (int i = 1; i < size; i++) {
            int key = b[i];
            m++;
            int p = position(b, i, key, c);

            for (int j = i; j > p; j--) {
                b[j] = b[j - 1];
                m++;
            }
            b[p] = key;
            m++;
        }
        };

    int b1[n] = {};
    copyArray(a, b1, n);
    int c1 = 0, m1 = 0;
    binarySort(b1, n, c1, m1);

    cout << "\nЗавдання 3. Бінарні вставки:\n";
    for (int x : b1) cout << x << " ";
    cout << "\nПорівнянь: " << c1
        << ", переміщень: " << m1 << endl;

    // завдання 4. шейкерне сортування
    auto shakerSort = [](int b[], int size, int& c, int& m,
        bool showBorders = false) {
            c = m = 0;
            int left = 0, right = size - 1;

            if (showBorders)
                cout << "Початкові межі: " << left << ", " << right << endl;

            while (left < right) {
                bool swapped = false;

                for (int i = left; i < right; i++) {
                    c++;
                    if (b[i] > b[i + 1]) {
                        int temp = b[i];
                        b[i] = b[i + 1];
                        b[i + 1] = temp;
                        m += 3;
                        swapped = true;
                    }
                }
                if (!swapped) break;
                right--;
                swapped = false;

                for (int i = right; i > left; i--) {
                    c++;
                    if (b[i - 1] > b[i]) {
                        int temp = b[i - 1];
                        b[i - 1] = b[i];
                        b[i] = temp;
                        m += 3;
                        swapped = true;
                    }
                }
                if (!swapped) break;
                left++;

                if (showBorders)
                    cout << "Нові межі: " << left << ", " << right << endl;
            }
        };

    int b2[n] = {};
    copyArray(a, b2, n);
    int c2 = 0, m2 = 0;

    cout << "\nЗавдання 4. Межі шейкерного сортування:\n";
    shakerSort(b2, n, c2, m2, true);

    cout << "Результат: ";
    for (int x : b2) cout << x << " ";
    cout << "\nПорівнянь: " << c2
        << ", переміщень: " << m2 << endl;

    // завдання 5. автоматична перевірка
    bool ok = true;
    for (int i = 0; i < n; i++)
        if (b1[i] != expected[i] || b2[i] != expected[i])
            ok = false;

    cout << "\nЗавдання 5. Перевірка: "
        << (ok ? "Успішно" : "Помилка") << endl;

    int keys[4] = { 1, 10, 20, 8 };
    int answersPos[4] = { 0, 3, 5, 3 };
    int passedPos = 0;

    for (int i = 0; i < 4; i++) {
        int count = 0;
        if (position(sample, 5, keys[i], count) == answersPos[i])
            passedPos++;
    }
    cout << "Перевірка позицій: " << passedPos << " / 4\n";

    int empty[1] = {};
    int single[1] = { 7 };
    int cc = 0, mm = 0;

    binarySort(empty, 0, cc, mm);
    shakerSort(empty, 0, cc, mm);
    binarySort(single, 1, cc, mm);
    shakerSort(single, 1, cc, mm);

    cout << "Граничні випадки: "
        << (single[0] == 7 ? "Успішно" : "Помилка") << endl;

    // завдання 6. порівняння з базовими алгоритмами
    auto insertion = [](int b[], int size, int& c, int& m) {
        c = m = 0;
        for (int i = 1; i < size; i++) {
            int key = b[i];
            m++;
            int j = i - 1;

            while (j >= 0) {
                c++;
                if (b[j] <= key) break;
                b[j + 1] = b[j];
                m++;
                j--;
            }
            b[j + 1] = key;
            m++;
        }
        };

    auto bubble = [](int b[], int size, int& c, int& m) {
        c = m = 0;
        for (int i = 0; i < size - 1; i++) {
            bool changed = false;

            for (int j = 0; j < size - i - 1; j++) {
                c++;
                if (b[j] > b[j + 1]) {
                    int temp = b[j];
                    b[j] = b[j + 1];
                    b[j + 1] = temp;
                    m += 3;
                    changed = true;
                }
            }
            if (!changed) break;
        }
        };

    int b3[n] = {}, b4[n] = {};
    copyArray(a, b3, n);
    copyArray(a, b4, n);

    int c3 = 0, m3 = 0, c4 = 0, m4 = 0;
    insertion(b3, n, c3, m3);
    bubble(b4, n, c4, m4);

    cout << "\nЗавдання 6. Порівняння:\n";
    cout << "Звичайні вставки: " << c3 << ", " << m3 << endl;
    cout << "Бінарні вставки: " << c1 << ", " << m1 << endl;
    cout << "Бульбашкове: " << c4 << ", " << m4 << endl;
    cout << "Шейкерне: " << c2 << ", " << m2 << endl;

    // завдання 7. експеримент на різних наборах
    int data[4][n] = {
        {1, 2, 4, 6, 7, 10, 13, 18, 21, 24, 27, 30},
        {30, 27, 24, 21, 18, 13, 10, 7, 6, 4, 2, 1},
        {18, 30, 4, 24, 7, 13, 2, 27, 10, 1, 21, 6},
        {5, 2, 5, 1, 2, 5, 1, 2, 5, 1, 2, 5}
    };

    cout << "\nЗавдання 7. Експеримент:\n";

    for (int t = 0; t < 4; t++) {
        cout << "Набір " << t + 1 << ":\n";

        for (int alg = 0; alg < 4; alg++) {
            int b[n] = {};
            copyArray(data[t], b, n);
            int countC = 0, countM = 0;

            if (alg == 0) insertion(b, n, countC, countM);
            if (alg == 1) binarySort(b, n, countC, countM);
            if (alg == 2) bubble(b, n, countC, countM);
            if (alg == 3) shakerSort(b, n, countC, countM);

            cout << "Алгоритм " << alg + 1
                << ": " << countC << " порівнянь, "
                << countM << " переміщень\n";
        }
    }

    // завдання 8. набір автоматизованих тестів
    int tests[8][5] = {
        {5, 4, 3, 2, 1},
        {1, 2, 3, 4, 5},
        {3, 1, 4, 2, 5},
        {2, 2, 2, 2, 2},
        {0, -1, 4, -3, 2},
        {9, 7, 5, 3, 1},
        {1, 1, 3, 2, 2},
        {8, 8, 3, 3, 1}
    };

    int answers[8][5] = {
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {2, 2, 2, 2, 2},
        {-3, -1, 0, 2, 4},
        {1, 3, 5, 7, 9},
        {1, 1, 2, 2, 3},
        {1, 3, 3, 8, 8}
    };

    int passed = 0;
    cout << "\nЗавдання 8. Автоматизовані тести:\n";

    for (int t = 0; t < 8; t++) {
        for (int alg = 0; alg < 2; alg++) {
            int b[5] = {};
            copyArray(tests[t], b, 5);

            int countC = 0, countM = 0;

            if (alg == 0)
                binarySort(b, 5, countC, countM);
            else
                shakerSort(b, 5, countC, countM);

            bool correct = true;
            for (int i = 0; i < 5; i++)
                if (b[i] != answers[t][i])
                    correct = false;

            if (correct) passed++;

            cout << "Тест " << t + 1
                << ", алгоритм " << alg + 1 << ": "
                << (correct ? "Успішно" : "Помилка") << endl;
        }
    }

    cout << "\nУспішних перевірок: "
        << passed << " / 16\n";

    return 0;
}