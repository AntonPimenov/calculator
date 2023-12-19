#include <iostream>
#include <cmath>
#include <clocale>

using namespace std;

struct fraction
{
    int nom, denom;
};

int gcd(int a, int b) // алгоритм Эвклида
{
    int r;
    while (r = a % b) // (r = a % b) != 0
    {
        a = b;
        b = r;
    }
    return b;
}

int power(int a, unsigned n)
{
    if (n == 0)
        return 1;
    int copy = a;
    for (int i = 1; i < n; ++i)
        a *= copy;
    return a;
}

//сокращение 
void reduce(fraction& a)
{
    if (a.denom < 0)
    {
        a.nom = -a.nom;
        a.denom = -a.denom;

    }
    int r = gcd(abs(a.nom), a.denom);
    a.nom /= r;
    a.denom /= r;
}

int nok(int a, int b)
{
    if (a < b)
    {
        int t;
        t = a;
        a = b;
        b = t;
    }
    int res = a;
    while (res % b)
        res += a;
    return res;
}

fraction mult(fraction a, fraction b)
{
    fraction result;
    reduce(a);
    reduce(b);
    int nd;
    nd = gcd(a.nom, b.denom);
    a.nom /= nd;
    b.denom /= nd;
    nd = gcd(b.nom, a.denom);
    b.nom /= nd;
    a.denom /= nd;
    result.nom = a.nom * b.nom;
    result.denom = a.denom * b.denom;
    return result;
}

fraction division(fraction a, fraction b)
{
    fraction c = { b.denom, b.nom };
    return mult(a, c);
}

fraction summa(fraction a, fraction b)
{
    fraction result;
    reduce(a);
    reduce(b);
    result.denom = nok(a.denom, b.denom);
    result.nom = result.denom / a.denom * a.nom + result.denom / b.denom * b.nom;
    reduce(result);
    return result;
}

fraction minuss(fraction a, fraction b)
{
    fraction result;
    reduce(a);
    reduce(b);
    result.denom = nok(a.denom, b.denom);
    result.nom = result.denom / a.denom * a.nom - result.denom / b.denom * b.nom;
    reduce(result);
    return result;
}

fraction power_f(fraction a, int n)
{
    reduce(a);
    if (n >= 0)
        return { power(a.nom, n), power(a.denom, n) };
    return { power(a.denom, abs(n)), power(a.nom, abs(n)) };
}

void print(const fraction& a)
{
    if (a.denom == 1)
        cout << a.nom;
    else if (abs(a.nom) < a.denom)
        cout << a.nom << '/' << a.denom;
    else
        cout << a.nom / a.denom << ' ' << abs(a.nom) % a.denom << '/' << a.denom;
}

void menu()
{
    cout << "МЕНЮ:\n";
    cout << "1. Сложение.\n";
    cout << "2. Вычитание.\n";
    cout << "3. Умножение.\n";
    cout << "4. Деление.\n";
    cout << "5. Возведение в степень.\n";
    cout << "6. Выход.\n";
    cout << "Выберите пункт меню: ";
}

fraction input()
{
    int x, y;
    cout << "Введите числитель: ";
    cin >> x;
    do
    {
        cout << "Введите знаменатель: ";
        cin >> y;
        if (y == 0)
            cout << "Ошибка: знаменатель не может быть равен нулю!\n";
        else
            break;
    } while (true);
    fraction res = { x, y };
    reduce(res);
    return res;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Калькулятор обыкновенных дробей" << '\n';
    int key, p;
    fraction a, b, c;
    do
    {
        menu();
        cin >> key;
        switch (key)
        {
        case 1:
            a = input();
            b = input();
            c = summa(a, b);
            cout << "Сумма дробей " << a.nom << "/" << a.denom << " и " << b.nom << "/" << b.denom << " равна  ";
            print(c);
            cout << '\n';
            break;
        case 2:
            a = input();
            b = input();
            c = minuss(a, b);
            cout << "Разность дробей " << a.nom << "/" << a.denom << " и " << b.nom << "/" << b.denom << " равна  ";
            print(c);
            cout << '\n';
            break;
        case 3:
            a = input();
            b = input();
            c = mult(a, b);
            cout << "Умножение дробей " << a.nom << "/" << a.denom << " и " << b.nom << "/" << b.denom << " равно  ";
            print(c);
            cout << '\n';
            break;
        case 4:
            a = input();
            do
            {
                b = input();
                if (b.nom == 0)
                    cout << "Ошибка: делитель не может быть равен нулю!\n";
                else
                    break;
            } while (true);
            c = division(a, b);
            cout << "Частное: ";
            print(c);
            cout << '\n';
            break;
        case 5:
            do
            {
                a = input();
                cout << "Введите показатель: ";
                cin >> p;                
                if (a.nom == 0 && p == 0)
                    cout << "Ошибка: неопределённость!\n";
                else
                    break;
            } while (true);
            c = power_f(a, p);
            cout << "Степень: ";
            print(c);
            cout << '\n';
            break;
            break;
        case 6:break;
        default: cout << "Неверный пункт меню!\n";
        }
    } while (key != 6);
}
/*
НОД(16, 14) = 2
НОК(16, 14) = 2 * 2 * 2 * 2 * 7 = 112
16 = 2 * 2 * 2 * 2
14 = 2 * 7

a * b = НОД(a, b) * НОК(a, b)
НОК(a, b) = a * b / НОД(a, b) = (a / НОД(a, b)) * b

16, 32, 48, 64, 80, 96, 112

a^n = a * a * ... * a

2^3 = 2 * 2 * 2


*/