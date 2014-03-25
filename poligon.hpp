#ifndef UUID_2DB3D893_EF52_4F08_92B2_565D95A63177
#define UUID_2DB3D893_EF52_4F08_92B2_565D95A63177

#include "alakzat.hpp"
#include <vector>

class Poligon : public Alakzat
{
public:
    Poligon(Pont p0, Szin sz) : Alakzat(sz), pts(2, p0) {}

    void Rajzol() const;
    bool Esemeny(SDL_Event& ev);

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
