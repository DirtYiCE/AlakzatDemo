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

bool Teglalap::Esemeny(SDL_Event& ev)
{
    if (ev.type == SDL_MOUSEMOTION)
    {
        p2 = Pont(ev.button.x, ev.button.y);
    }
    else if (ev.type == SDL_MOUSEBUTTONUP)
        return false;

    return true;
}

Teglalap* TeglalapFactory::Create(Pont p, Szin sz) const
{
    return new Teglalap(p, p, sz);
}
