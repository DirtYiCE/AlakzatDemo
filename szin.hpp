#ifndef UUID_E222DD95_B979_4972_8482_E7BA518BE9E4
#define UUID_E222DD95_B979_4972_8482_E7BA518BE9E4

#include <iostream>

// egy RGB szint tarol. struct, hasonlokepp a Ponthoz.
struct Szin
{
    unsigned char r, g, b, a;

    Szin() : r(255), g(255), b(255), a(255) {}
    Szin(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
        : r(r), g(g), b(b), a(a) {}
};

inline std::ostream& operator<<(std::ostream& os, const Szin& s)
{
    os << "Szin(" << int(s.r) << ", " << int(s.g) << ", " << int(s.b) << ", "
       << int(s.a) << ")";
    return os;
}

#endif
