#ifndef UUID_EF9F25F5_4627_41BA_A941_3D3BD0B0C9BE
#define UUID_EF9F25F5_4627_41BA_A941_3D3BD0B0C9BE

#include "alakzat.hpp"
#include "pont.hpp"

// egy teglalapot rajzol bal felso, jobb also koordinatakbol
class Teglalap : public Alakzat
{
public:
    Teglalap(Pont p1, Pont p2, Szin sz) : Alakzat(sz), p1(p1), p2(p2) {}

    void Rajzol() const;
    void Mozgat(Pont p);
    bool Esemeny(SDL_Event& ev);

private:
    Pont p1, p2;
};

class TeglalapFactory : public AlakzatFactory
{
public:
    Teglalap* Create(Pont p, Szin sz) const;
    const char* Nev() const { return "teglalap"; }
};

#endif
