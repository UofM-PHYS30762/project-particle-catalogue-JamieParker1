#ifndef INDIVIDUAL_QUARKS_H
#define INDIVIDUAL_QUARKS_H

#include "QuarkTemplate.h"

template<>
struct QuarkName<7> {
    static constexpr char name[7] = "bottom";
};

template<>
struct QuarkName<6> {
    static constexpr char name[6] = "charm";
};

template<>
struct QuarkName<5> {
    static constexpr char name[5] = "down";
};

template<>
struct QuarkName<3> {
    static constexpr char name[3] = "up";
};

template<>
struct QuarkName<8> {
    static constexpr char name[8] = "strange";
};

template<>
struct QuarkName<4> {
    static constexpr char name[4] = "top";
};

class Bottom_test : public QuarkTemplate<Bottom_test, QuarkName<7>, 1, 3, 4180, 1> {};
class Charm_test : public QuarkTemplate<Charm_test, QuarkName<6>, 2, 3, 1275, 1> {};
class Down_test : public QuarkTemplate<Down_test, QuarkName<5>, 1, 3, 48, 10> {};
class Up_test : public QuarkTemplate<Up_test, QuarkName<3>, 2, 3, 23, 10> {};
class Strange_test : public QuarkTemplate<Strange_test, QuarkName<8>, 1, 3, 95, 1> {};
class Top_test : public QuarkTemplate<Top_test, QuarkName<4>, 2, 3, 173070, 1> {};

#endif // INDIVIDUAL_QUARKS_H