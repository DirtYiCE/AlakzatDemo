#include "kor.hpp"
#include <SDL_gfxPrimitives.h>

// normal esetbe ez egy headerbe menne, de most nem fogok egy sorert egy kulon
// headert irni...
extern SDL_Surface* screen;

void Kor::Rajzol() const
{
    // kirajzoljuk a kort adott pontban es sugarral
    Szin s = GetSzin();
    circleRGBA(screen, p.x, p.y, r, s.r, s.g, s.b, s.a);
}

void Kor::Mozgat(Pont pont)
{
    p += pont;
}

void Kor::UserRajzol(Pont pont)
{
    r = (p-pont).Length();
}

Kor* KorFactory::Create(Pont p, Szin sz) const
{
    return new Kor(p, 0, sz);
}
