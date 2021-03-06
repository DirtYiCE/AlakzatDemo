#ifndef UUID_9839AF66_BB16_4670_8416_34ED1E58CC5C
#define UUID_9839AF66_BB16_4670_8416_34ED1E58CC5C

#include <SDL.h>
#include "pont.hpp"
#include "szin.hpp"

// az alap alakzat. a laboros feladathoz kepest a pozicio tarolast kivettem
// innen, igy azt a leszarmazottak ugy oldjak meg, ahogy akarjak.
class Alakzat
{
public:
    // az alakzatnak csak szine van
    Alakzat(Szin szin) : szin(szin) {}

    // virtualis destruktor, mert ha nem. na abbol nagy baj lesz:
    // http://www.parashift.com/c++-faq/virtual-dtors.html
    virtual ~Alakzat() {}

    // alakzat kirajzolasa. hogy hogyan, az az alakzat dolga, mi nem
    // tudjuk. ezert pure virtual. cserebe nem lehet belole peldanyt
    // letrehozni. (akik korabban hasznaltak c#/javat: ott ezt abstract
    // fuggvenynek hivjak)
    virtual void Rajzol() const = 0;

    // az alakzat eltolasa p-vel. pure virtual, mivel itt az alakzat nem tudja
    // hol van -- az csak a leszarmazottakban van eltarolva
    virtual void Mozgat(Pont p) = 0;

    // akkor hivodok meg amikor a felhasznalo lenyomva tartva a bal gombot huzza
    // az egeret. kor eseten ez atmeretezi a kor sugarat, teglalapnal a jobb
    // also sarkot hatarozza meg, stb.
    virtual void UserRajzol(Pont p) = 0;

    // akkor hivodik meg, amikor a felhasznalo rajzolas kozben jobb gombbal
    // kattint. poligonnal ez uj pontot vesz fel, kornel es tegalalpnal nem
    // csinal semmit.
    virtual void UserKattint() {}

    const Szin& GetSzin() const { return szin; }
private:
    Szin szin;
};


// egy osztaly ami alakzatot gyart. a leszarmazottak fognak kulonbozo alakzatot
// gyartani. lasd a main.cpp-t hogy miert is jo ez.
class AlakzatFactory
{
public:
    virtual ~AlakzatFactory() {}

    virtual Alakzat* Create(Pont p, Szin sz) const = 0;
    // virtual konstans nem letezik, ez a masodik legjobb megoldas erre...
    virtual const char* Nev() const = 0;
};

#endif
