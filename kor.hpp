#ifndef UUID_CADD3B79_7363_44C7_B179_E7429F8AE4CC
#define UUID_CADD3B79_7363_44C7_B179_E7429F8AE4CC

#include "alakzat.hpp"
#include "pont.hpp"

// egy kort rajzol. kor megadasa: kozeppont, sugar
class Kor : public Alakzat
{
public:
    Kor(Pont p, int r, Szin sz) : Alakzat(sz), p(p), r(r) {}

    void Rajzol() const;
    void Mozgat(Pont pont);
    void UserRajzol(Pont p);

private:
    Pont p;
    int r;
};

class KorFactory : public AlakzatFactory
{
public:
    Kor* Create(Pont p, Szin sz) const;
    const char* Nev() const { return "kor"; }
};

#endif
