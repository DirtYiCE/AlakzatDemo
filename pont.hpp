#ifndef UUID_B215816D_17A4_4F83_8B1F_974B2C3399F7
#define UUID_B215816D_17A4_4F83_8B1F_974B2C3399F7

#include <iostream>
#include <math.h>

// egy x-y koordinata part tarol, nehany hasznos fuggvennyel. nem kell az
// objektumorientaltsagot es adatrejtest eroltetni ahol nem kell, egy pont az
// all egy x es y koordinatabol, amit barhogy modosithatunk, nem romlik el az
// objektum belso allapota. teny, igy kesobbiekben nem allhatunk at polar
// koordinatakra a kod modositasa nelkul, de ez jelen esetben nem is
// valoszeru. igazabol ez inkabb egy mezei c struct, csak kicsit felturbozva.
//
// c++-ban a struct es class kozott nincs kulonbseg (csak hogy a class memberjei
// alapbol private-ek, mig a struct-e public-ok), azonban az egy jo programozoi
// strategia lehet hogy a class-t hasznaljuk igazi osztalyokra, a struct-ot
// pedig olyan objektumokra amik igy public adattagokat tartalmaz, csak van
// nehany helper method pluszba.
struct Pont
{
    int x, y;

    Pont() : x(0), y(0) {}
    Pont(int x, int y) : x(x), y(y) {}

    Pont& operator-=(const Pont& o)
    {
        x -= o.x;
        y -= o.y;
        return *this;
    }

    Pont operator-(const Pont& o) const
    {
        // operator- visszavezetese operator-= re. ezt persze nagyjabol az
        // osszes akarmi= operatorra megt lehet csinalni, boost-ba peldaul van
        // erre egy konyvtar:
        // http://www.boost.org/doc/libs/1_55_0/libs/utility/operators.htm
        Pont r(*this);
        r -= o;
        return r;
    }


    Pont& operator+=(const Pont& o)
    {
        x += o.x;
        y += o.y;
        return *this;
    }

    Pont operator+(const Pont& o) const
    {
        Pont r(*this);
        r += o;
        return r;
    }


    // ha a pontot vektorkent kepzeljuk el, mi a hossza. ez megint az az eset
    // ahol kicsit osszefolynak eltero dolgot, ugyanis egy pontot es egy vektort
    // is x-y koordinatakkent tarolunk. pontot igazabol csak vekorral van
    // ertelme eltolni, vektort nincs ertelme eltolni, pontnak nincs hossza,
    // stb. de a sok hasonlosag miatt szokas ezt igy egybe kezelni.
    double Length() const { return sqrt(x*x+y*y); }
};

inline std::ostream& operator<<(std::ostream& os, const Pont& p)
{
    return os << "Pont(" << p.x << ", " << p.y << ")";
}

#endif
