#ifndef UUID_2DB3D893_EF52_4F08_92B2_565D95A63177
#define UUID_2DB3D893_EF52_4F08_92B2_565D95A63177

#include "alakzat.hpp"
#include <vector>

// egy poligon korvanalak kirajzolasa. a pontokat egy std::vector tarolja, hogy
// egyszeruen kezelheto legyen tetszoleges szamu pont.
class Poligon : public Alakzat
{
public:
    Poligon(Pont p0, Szin sz) : Alakzat(sz), pts(2, p0) {}

    void Rajzol() const;
    void Mozgat(Pont p);
    void UserRajzol(Pont p);
    void UserKattint();

private:
    std::vector<Pont> pts;
};

class PoligonFactory : public AlakzatFactory
{
public:
    Poligon* Create(Pont p, Szin sz) const;
    const char* Nev() const { return "poligon"; }
};

#endif
