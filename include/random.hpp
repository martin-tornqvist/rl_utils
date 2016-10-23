#ifndef RL_UTILS_RANDOM_HPP
#define RL_UTILS_RANDOM_HPP

struct DiceParam
{
    DiceParam() :
        rolls   (0),
        sides   (0),
        plus    (0) {}

    DiceParam(const int rolls, const int sides, const int plus = 0) :
        rolls   (rolls),
        sides   (sides),
        plus    (plus) {}

    DiceParam(const DiceParam& other) :
        rolls   (other.rolls),
        sides   (other.sides),
        plus    (other.plus) {}

    DiceParam& operator=(const DiceParam& other)
    {
        rolls = other.rolls;
        sides = other.sides;
        plus  = other.plus;
        return *this;
    }

    int max() const
    {
        return (rolls * sides) + plus;
    }

    int min() const
    {
        return (rolls + plus);
    }

    int roll() const;

    int rolls, sides, plus;
};

struct Range
{
    Range() :
        min(-1),
        max(-1) {}

    Range(const int min, const int max) :
        min(min),
        max(max) {}

    Range(const Range& other) :
        Range(other.min, other.max) {}

    int len() const
    {
        return max - min + 1;
    }

    bool is_in_range(const int v) const
    {
        return v >= min && v <= max;
    }

    void set(const int min_val, const int max_val)
    {
        min = min_val;
        max = max_val;
    }

    Range& operator/=(const int v)
    {
        min /= v;
        max /= v;
        return *this;
    }

    int roll() const;

    int min, max;
};

struct Fraction
{
    Fraction() :
        num(-1),
        den(-1) {}

    Fraction(const int num, const int den) :
        num(num),
        den(den) {}

    void set(const int numer, const int denom)
    {
        num = numer;
        den = denom;
    }

    bool roll() const;

    int num, den;
};

//------------------------------------------------------------------------------
// Random number generation
//------------------------------------------------------------------------------
namespace rnd
{

// void seed(const unsigned long val);

// NOTE: If not called with a positive non-zero number of sides, this will
//        always return zero.
int dice(const int rolls, const int sides);

bool coin_toss();

bool fraction(const int numer, const int denom);

bool one_in(const int N);

// Can be called with any range (positive or negative), V2 does *not* have to be
// bigger than V1.
int range(const int v1, const int v2);

// NOTE: "p" shall be within [0.0, 1.0]
int range_binom(const int v1, const int v2, const double p);

int percent();

bool percent(const int pct_chance);

int weighted_choice(const std::vector<int> weights);

template <typename T>
T element(const std::vector<T>& vec)
{
    const size_t idx = range(0, vec.size() - 1);

    return vec[idx];
}

template <typename T>
size_t idx(const std::vector<T>& vec)
{
    return range(0, vec.size() - 1);
}

} // rnd

#endif // RL_UTILS_RANDOM_HPP
