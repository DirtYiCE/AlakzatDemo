#include "teglalap.hpp"
#include <SDL_gfxPrimitives.h>

// normal esetbe ez egy headerbe menne, de most nem fogok egy sorert egy kulon
// headert irni...
extern SDL_Surface* screen;

void Teglalap::Rajzol() const
{
    Szin s = GetSzin();
    rectangleRGBA(screen, p1.x, p1.y, p2.x, p2.y, s.r, s.g, s.b, s.a);
}

void Teglalap::Mozgat(Pont p)
{
    p1 += p;
    p2 += p;
}

void Teglalap::UserRajzol(Pont p)
{
    p2 = p;
}

Teglalap* TeglalapFactory::Create(Pont p, Szin sz) const
{
    return new Teglalap(p, p, sz);
}
