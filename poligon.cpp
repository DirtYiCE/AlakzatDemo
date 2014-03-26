#include "poligon.hpp"
#include <SDL_gfxPrimitives.h>

extern SDL_Surface* screen;

void Poligon::Rajzol() const
{
    Szin s = GetSzin();
    // paronkent vegigmegyunk az osszes ponton, es osszekotjuk oket
    for (size_t i = 1; i < pts.size(); ++i)
        lineRGBA(screen, pts[i-1].x, pts[i-1].y, pts[i].x, pts[i].y,
                 s.r, s.g, s.b, s.a);
}

void Poligon::Mozgat(Pont p)
{
    for (size_t i = 0; i < pts.size(); ++i)
        pts[i] += p;
}

void Poligon::UserRajzol(Pont p)
{
    pts.back() = p;
}

void Poligon::UserKattint()
{
    pts.push_back(pts.back());
}

Poligon* PoligonFactory::Create(Pont p, Szin sz) const
{
    return new Poligon(p, sz);
}
