// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len <= 0) {
        throw "длина отрицательная";
    }
    BitLen = len;
    MemLen = (BitLen + 8 * sizeof(TELEM) - 1) / (8 * sizeof(TELEM));
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField& bf){
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0;i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    TELEM res = 1;
    int idBit = n % (sizeof(TELEM) * 8);
    res <<= idBit;
    return res;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= BitLen) throw ("неверное значение");
    int id = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    pMem[id] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen) throw ("неверное значение");
    int id = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    pMem[id] &= ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    int id = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    int res = pMem[id];
    res &= mask;
    if (res == 0) return 0;
    else return 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf) {
        delete[] pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int maxLen = BitLen;
    if (bf.BitLen > maxLen) { maxLen = bf.BitLen; }
    TBitField result(maxLen);
    for (int i = 0; i < maxLen; i++)
    {
        int bit1 = 0;
        int bit2 = 0;
        if (i < BitLen) { bit1 = GetBit(i); }
        if (i < bf.BitLen){bit2 = bf.GetBit(i);}
        if (bit1 || bit2){result.SetBit(i);}
    }

    return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int maxLen = BitLen;
    if (bf.BitLen > maxLen) { maxLen = bf.BitLen; }

    TBitField result(maxLen);

    for (int i = 0; i < maxLen; i++)
    {
        int bit1 = 0;
        int bit2 = 0;
        if (i < BitLen) { bit1 = GetBit(i); }
        if (i < bf.BitLen) { bit2 = bf.GetBit(i); }
        if (bit1 && bit2) { result.SetBit(i); }
    }

    return result;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField result(BitLen);
    for (int i = 0; i < BitLen; i++)
    {
        if (!GetBit(i))
            result.SetBit(i);
    }
    return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    for (int i = 0; i < bf.BitLen; i++) {
        char c;
        istr >> c;
        if (c == '1')
            bf.SetBit(i);
        else
            bf.ClrBit(i);
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = bf.BitLen - 1; i >= 0; i--)
    {
        ostr << bf.GetBit(i);
    }

        return ostr;
}

bool TBitField::operator==(const TBitField& bf) const {
    if (bf.BitLen != BitLen) return false;
    for (int i = 0; i < MemLen - 1; i++) {
        if (pMem[i] != bf.pMem[i]) return false;
    }
    for (int i = (MemLen - 1) * sizeof(TELEM) * 8;i < BitLen;i++) {
        if (bf.GetBit(i) != GetBit(i)) return false;
    }
    return true;
}

bool TBitField::operator!=(const TBitField& bf) const
{
    return !(*this == bf);
}

