#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

// ------------------ Константы ------------------
const double g = 9.81;       // ускорение свободного падения
const double rho0 = 1.225;   // плотность воздуха на уровне моря

// ---------- Функции для повторяющихся формул ---
double Lift(double p, double V, double S, double CL) {
    return 0.5 * p * V * V * S * CL;
}
double Drag(double p, double V, double S, double CD) {
    return 0.5 * p * V * V * S * CD;
}

// --------------------- Задачи -------------------
void Zadacha1() {
    cout << "\n--- Задача 1: Подъемная сила ---\n";
    double S, V, p, CL;
    cout << "Площадь S: "; cin >> S;
    cout << "Скорость V: "; cin >> V;
    cout << "Плотность p: "; cin >> p;
    cout << "Коэффициент CL: "; cin >> CL;

    double L = Lift(p, V, S, CL);
    cout << "Подъемная сила: " << L << " Н\n";
}

void Zadacha2() {
    cout << "\n--- Задача 2: Сопротивление ---\n";
    double S, V, p, CD;
    cout << "Площадь крыла: "; cin >> S;
    cout << "Скорость: "; cin >> V;
    cout << "Плотность воздуха: "; cin >> p;
    cout << "CD: "; cin >> CD;

    cout << "Сопротивление: " << Drag(p, V, S, CD) << " Н\n";
}

void Zadacha3() {
    cout << "\n--- Задача 3: Ускорения ЛА ---\n";
    double m, L, D, T;
    cout << "Масса: "; cin >> m;
    cout << "Подъемная сила: "; cin >> L;
    cout << "Сопротивление: "; cin >> D;
    cout << "Тяга двигателя: "; cin >> T;

    cout << "Ускорение вперед: " << (T - D) / m << " м/с^2\n";
    cout << "Ускорение вверх: " << (L - m * g) / m << " м/с^2\n";
}

void Zadacha4() {
    cout << "\n--- Задача 4: Время набора высоты ---\n";
    double ay, h;
    cout << "Ускорение вверх: "; cin >> ay;
    cout << "Высота: "; cin >> h;

    if (ay <= 0 || h <= 0) {
        cout << "Ошибка: Значения должны быть положительными!\n";
        return;
    }
    cout << "Время: " << sqrt(2 * h / ay) << " c\n";
}

void Zadacha5() {
    cout << "\n--- Задача 5: Сравнение 3 самолетов ---\n";

    struct Plane { string name; double m, S, T, CD, CL; };
    Plane A[3] = {
        {"Plane A", 15000, 40, 80000, 0.03, 1.2},
        {"Plane B", 20000, 50, 100000, 0.04, 1.1},
        {"Plane C",  9000, 22, 20000, 0.05, 1.3}
    };

    double best = 1e9;
    string bestName;
    double V = 90;

    for (int i = 0; i < 3; i++) {
        double L = Lift(rho0, V, A[i].S, A[i].CL);
        double ay = (L - A[i].m * g) / A[i].m;
        double t = (ay > 0) ? sqrt(2 * 1000 / ay) : 1e9;
        cout << A[i].name << " — t=" << t << " c\n";

        if (t < best) {
            best = t;
            bestName = A[i].name;
        }
    }
    cout << "Самый быстрый — " << bestName << "\n";
}

void Zadacha6() {
    cout << "\n--- Задача 6: Подъемная сила на траектории ---\n";
    double V[6] = { 80,100,130,170,200,160 };
    double p[6] = { 1.22,1.18,1.05,0.9,0.7,0.95 };
    double S = 50, CL = 1.1;

    cout << "Шаг | Скорость | Плотность | Подъемная сила\n";
    for (int i = 0; i < 6; i++) {
        double L = Lift(p[i], V[i], S, CL);
        cout << i + 1 << " | " << V[i] << " | " << p[i] << " | " << L << "\n";
    }
}

void Zadacha7() {
    cout << "\n--- Задача 7: Режим полета ---\n";
    double T, L, D, m;
    cout << "Тяга: "; cin >> T;
    cout << "Подъем: "; cin >> L;
    cout << "Сопротивление: "; cin >> D;
    cout << "Масса: "; cin >> m;

    double a = (T - D) / m;

    if (a > 0.5) cout << "Режим: Набор высоты\n";
    else if (a >= 0) cout << "Режим: Горизонтальный полет\n";
    else cout << "Режим: Снижение\n";
}

void Zadacha8() {
    cout << "\n--- Задача 8: Несколько самолетов и сортировка ---\n";

    struct Air { string name; double m, T, CL, CD; };
    Air arr[3] = {
        {"A",12000,60000,1.3,0.12},
        {"B",30000,150000,1.0,0.2},
        {"C", 9000,20000,1.5,0.1}
    };

    const double h = 5000;
    double V = 150, S = 40;

    for (int i = 0; i < 3; i++) {
        double L = Lift(rho0, V, S, arr[i].CL);
        double D = Drag(rho0, V, S, arr[i].CD);
        double ay = (L - arr[i].m * g) / arr[i].m;
        double t = (ay > 0) ? sqrt(2 * h / ay) : 99999;
        cout << arr[i].name << " t=" << t << " c\n";
    }
}

void Zadacha9() {
    cout << "\n--- Задача 9: Пользователь вводит самолёты ---\n";

    int n;
    cout << "Сколько самолетов? ";
    cin >> n;

    vector<string> name(n);
    vector<double> m(n), S(n), T(n), CD(n);

    for (int i = 0; i < n; i++) {
        cout << "Название: "; cin >> name[i];
        cout << "Масса: "; cin >> m[i];
        cout << "Площадь: "; cin >> S[i];
        cout << "Тяга: "; cin >> T[i];
        cout << "CD: "; cin >> CD[i];
        cout << "\n";
    }

    cout << "Результаты:\n";
    int best = 0;
    for (int i = 0; i < n; i++) {
        double D = Drag(rho0, 150, S[i], CD[i]);
        double a = (T[i] - D) / m[i];
        cout << name[i] << " ускорение: " << a << endl;
        if (a > (T[best] - Drag(rho0, 150, S[best], CD[best])) / m[best])
            best = i;
    }
    cout << "Лидер: " << name[best] << endl;
}

void Zadacha10() {
    cout << "\n--- Задача 10: Поиск оптимальной тяги ---\n";
    double Tmin, Tmax, dT;
    cout << "Мин тяга: "; cin >> Tmin;
    cout << "Макс тяга: "; cin >> Tmax;
    cout << "Шаг: "; cin >> dT;

    double bestT = Tmin, best = 1e9;
    const double m = 15000, S = 40, CD = 0.08, CL = 1.2;
    double L = Lift(rho0, 150, S, CL);
    double D = Drag(rho0, 150, S, CD);

    for (double T = Tmin; T <= Tmax; T += dT) {
        double ay = (L - m * g) / m;
        double ax = (T - D) / m;
        double a = ay + ax * 0.2;
        double t = (a > 0) ? sqrt(2 * 4000 / a) : 1e9;
        cout << "T=" << T << " t=" << t << endl;

        if (t < best) {
            best = t;
            bestT = T;
        }
    }
    cout << "Оптимум: T=" << bestT << " Время=" << best << " c\n";
}

// ------------------ Главное меню -------------------
int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    do {
        cout << "\n=========== МЕНЮ ЗАДАЧ ===========\n";
        cout << "1 - Подъемная сила\n";
        cout << "2 - Сопротивление\n";
        cout << "3 - Ускорение ЛА\n";
        cout << "4 - Время набора высоты\n";
        cout << "5 - Сравнение 3 самолётов\n";
        cout << "6 - Подъем на траектории\n";
        cout << "7 - Режим полёта\n";
        cout << "8 - Несколько самолётов\n";
        cout << "9 - Ввод N самолётов\n";
        cout << "10 - Оптимальная тяга\n";
        cout << "0 - Выход\n";
        cout << "Выберите задачу: ";
        cin >> choice;

        switch (choice) {
        case 1: Zadacha1(); break;
        case 2: Zadacha2(); break;
        case 3: Zadacha3(); break;
        case 4:Zadacha4(); break;
        case 5: Zadacha5(); break;
        case 6: Zadacha6(); break;
        case 7: Zadacha7(); break;
        case 8: Zadacha8(); break;
        case 9: Zadacha9(); break;
        case 10: Zadacha10(); break;
        case 0: cout << "Выход...\n"; break;
        default: cout << "Нет такой задачи!\n";
        }
    } while (choice != 0);

    return 0;
}
