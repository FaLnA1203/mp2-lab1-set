// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_prime_numbers.cpp - Copyright (c) Гергель В.П. 20.08.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Тестирование битового поля и множества

#include <iomanip>

// #define USE_SET // Использовать класс TSet,
                // закоментировать, чтобы использовать битовое поле

//#ifndef USE_SET // Использовать класс TBitField

#include "tbitfield.h"

/*int main()
{
  int n, m, k, count;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование программ поддержки битового поля" << endl;
  cout << "             Решето Эратосфена" << endl;
  cout << "Введите верхнюю границу целых значений - ";
  cin  >> n;
  TBitField s(n + 1);
  // заполнение множества
  for (m = 2; m <= n; m++)
    s.SetBit(m);
  // проверка до sqrt(n) и удаление кратных
  for (m = 2; m * m <= n; m++)
    // если m в s, удаление кратных
    if (s.GetBit(m))
      for (k = 2 * m; k <= n; k += m)
        if (s.GetBit(k))
          s.ClrBit(k);
  // оставшиеся в s элементы - простые числа
  cout << endl << "Печать множества некратных чисел" << endl << s << endl;
  cout << endl << "Печать простых чисел" << endl;
  count = 0;
  k = 1;
  for (m = 2; m <= n; m++)
    if (s.GetBit(m))
    {
      count++;
      cout << setw(3) << m << " ";
      if (k++ % 10 == 0)
        cout << endl;
    }
  cout << endl;
  cout << "В первых " << n << " числах " << count << " простых" << endl;
}
#else

#include "tset.h"

int main()
{
  int n, m, k, count;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование программ поддержки множества" << endl;
  cout << "              Решето Эратосфена" << endl;
  cout << "Введите верхнюю границу целых значений - ";
  cin  >> n;
  TSet s(n + 1);
  // заполнение множества
  for (m = 2; m <= n; m++)
    s.InsElem(m);
  // проверка до sqrt(n) и удаление кратных
  for (m = 2; m * m <= n; m++)
    // если м в s, удаление кратных
    if (s.IsMember(m))
      for (k = 2 * m; k <= n; k += m)
       if (s.IsMember(k))
         s.DelElem(k);
  // оставшиеся в s элементы - простые числа
  cout << endl << "Печать множества некратных чисел" << endl << s << endl;
  cout << endl << "Печать простых чисел" << endl;
  count = 0;
  k = 1;
  for (m = 2; m <= n; m++)
    if (s.IsMember(m))
    {
      count++;
      cout << setw(3) << m << " ";
      if (k++ % 10 == 0)
        cout << endl;
    }
  cout << endl;
  cout << "В первых " << n << " числах " << count << " простых" << endl;
}

#endif*/

#include <iostream>
#include "tbitfield.h"
using namespace std;

int main()
{
    // Создание поля длины 10 (все нули)
    TBitField a(10);
    cout << "a (new, len=10): " << a << endl;

    // Установка битов
    a.SetBit(0);
    a.SetBit(5);
    a.SetBit(9);
    cout << "a after Set(0,5,9): " << a << endl;

    // Сброс бита
    a.ClrBit(5);
    cout << "a after Clr(5): " << a << endl;

    // Чтение бита
    cout << "a.GetBit(0)=" << a.GetBit(0)
        << " a.GetBit(5)=" << a.GetBit(5)
        << " a.GetBit(9)=" << a.GetBit(9) << endl;

    // Конструктор копирования
    TBitField b(a);
    cout << "b (copy of a): " << b << endl;

    b.ClrBit(0);
    cout << "b after Clr(0): " << b << endl;
    cout << "a unchanged:   " << a << endl;

    // operator=
    TBitField c(4);
    c = a;
    cout << "c (c=a, len was 4): " << c << endl;

    // operator>>
    TBitField d(10);
    cout << "Enter 10 bits (0/1): ";
    cin >> d;
    cout << "d: " << d << endl;

    // Проверка границ TELEM
    const int B = 8 * sizeof(TELEM);
    TBitField e(B + 2);
    e.SetBit(B - 1);
    e.SetBit(B);
    cout << "e (len=" << B + 2 << ", bits " << B - 1 << " and " << B << "): " << e << endl;

    // Исключения при выходе за диапазон
    try { a.SetBit(-1); }
    catch (...) { cout << "SetBit(-1) -> exception OK" << endl; }

    try { a.ClrBit(10); }
    catch (...) { cout << "ClrBit(10) -> exception OK" << endl; }

    return 0;
}