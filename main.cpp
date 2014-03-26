#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <iostream>
#include <vector>

#include "alakzat.hpp"
#include "kor.hpp"
#include "poligon.hpp"
#include "teglalap.hpp"

// globalis valtozo: nem szep, de hasznos
SDL_Surface* screen = NULL;

// az aktiv rajzolasi szin indexe az alabbi tombben
static int akt_szin = 0;
static const struct SzinInfo
{
    Szin szin;
    const char* nev;
} szinek[] = {
    { Szin(255, 0, 0),     "piros" },
    { Szin(0, 255, 0),     "zold" },
    { Szin(0, 0, 255),     "kek" },
    { Szin(255, 255, 0),   "sarga" },
    { Szin(255, 255, 255), "feher" },
};
// a tomb hossza kis c magiaval
static const size_t num_szinek = sizeof(szinek)/sizeof(szinek[0]);

// az alakzatok hasonloan. azonban itt egy kis trukkozes kell, nem eleg az
// alakzatok tipusat eltarolni, uj peldanyokat is letre kell hozni. erre jo az
// AlakzatFactory, ami tudja egy alakzat nevet es hogyan kell letrehozni. ez igy
// meg mindig kicsit ronda, hogy itt egyesevel fel kell sorolni az osszes
// alakzatot, ennek megoldasa viszont azt hiszem mar a jovore (remelhetoleg)
// indulo halado c++ kurzus anyaga...
static int akt_fact = 0;
static AlakzatFactory const* const facts[] = {
    new KorFactory(),
    new TeglalapFactory(),
    new PoligonFactory(),
};
static const size_t num_facts = sizeof(facts)/sizeof(facts[0]);

void KeyEvent(SDL_KeyboardEvent& ev)
{
    switch (ev.keysym.sym)
    {
    case SDLK_q:
        if (--akt_szin < 0) akt_szin = num_szinek-1;
        break;
    case SDLK_e:
        akt_szin = (akt_szin + 1) % num_szinek;
        break;

    case SDLK_z:
    case SDLK_y:
        if (--akt_fact < 0) akt_fact = num_facts-1;
        break;
    case SDLK_x:
        akt_fact = (akt_fact + 1) % num_facts;
        break;
    }
}

int main(int argc, char** argv)
{
    // inicializalas
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(800, 600, 0, SDL_ANYFORMAT);
    if (!screen)
    {
        std::cerr << "SetVideoMode failed" << std::endl;
        return 1;
    }
    SDL_WM_SetCaption("Alakzat demo", "Alakzat demo");

    // az std::vector egy olyan osztaly, ami egy dinamikusan novo tombot
    // hasznal. gyakorlatilag mint a dinsztring osztalyok amiket idaig irtunk,
    // csak nem stringet tarol, hanem tetszoleges tipusu tombot. a <> arra utal
    // hogy generikus tipus, elvileg a mostani eloadason lesz rola szo. az
    // std::vector-rol ha jol latom 10. het, de azert szerintem fuggvenyek
    // neveibol egyertelmuen kitalalhato mi mit csinal...
    std::vector<Alakzat*> alakzatok;

    // a kivalasztott alakzat
    Alakzat* selected = NULL;
    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT)
    {
        if (ev.type == SDL_KEYDOWN)
            KeyEvent(ev.key);
        else if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT)
        {
            // hozzaadunk egy uj alakzatot az alakzatokhoz
            alakzatok.push_back(facts[akt_fact]->Create(
                Pont(ev.button.x, ev.button.y), szinek[akt_szin].szin));
            // a kijelolt alakzat a most hozzaadot (az elobb a vegere adtuk
            // hozza az elemet, tehat a tomb vege az uj elem)
            selected = alakzatok.back();
        }
        else if (ev.type == SDL_MOUSEMOTION && ev.motion.state == SDL_BUTTON_MIDDLE)
            for (size_t i = 0; i < alakzatok.size(); ++i)
                alakzatok[i]->Mozgat(Pont(ev.motion.xrel, ev.motion.yrel));
        else if (selected && !selected->Esemeny(ev))
            selected = NULL;

        // rajzolas: letoroljuk a kepernyot
        SDL_FillRect(screen, NULL, 0);
        // minden alakzatot kirajzolunk
        for (size_t i = 0; i < alakzatok.size(); ++i)
            alakzatok[i]->Rajzol();

        // allapotinformaciok megjelenitese
        stringRGBA(screen, 0, 0, "Szin:", 255,255,255,255);
        stringRGBA(screen, 48, 0, szinek[akt_szin].nev, 255,255,255,255);
        stringRGBA(screen, 0, 10, "Alakzat:", 255,255,255,255);
        stringRGBA(screen, 72, 10, facts[akt_fact]->Nev(), 255,255,255,255);
        // megjelenitjuk amit eddig rajzoltunk
        SDL_Flip(screen);
    }

    // mivel az tombbe pointerek vannak, azokat nekunk kell felszabaditani. a
    // tombot magat mar nem, azt az std::vector megoldja.
    // amugy erre is van megoldas hogy ilyet ne kelljen, smart pointerekkel, de
    // ez mar nincs benne az idei tananyagba
    for (size_t i = 0; i < alakzatok.size(); ++i)
        delete alakzatok[i];
    // a factories-el is kell kezdeni valamit, ugyanigy
    for (size_t i = 0; i < num_facts; ++i)
        delete facts[i];

    // az SDL az alapvetoen egy c-s csoda, nekunk kell manualisan leallitani
    SDL_Quit();
    return 0;
}
