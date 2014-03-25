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

bool Poligon::Esemeny(SDL_Event& ev)
{
    if (ev.type == SDL_MOUSEMOTION)
    {
        pts.back() = Pont(ev.button.x, ev.button.y);
    }
    else if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_RIGHT)
        pts.push_back(pts.back());
    else if (ev.type == SDL_MOUSEBUTTONUP && ev.button.button == SDL_BUTTON_LEFT)
        return false;

    return true;
}

Poligon* PoligonFactory::Create(Pont p, Szin sz) const
{
    return new Poligon(p, sz);
}
