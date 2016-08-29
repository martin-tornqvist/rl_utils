#include "rl_utils.hpp"

#include "mersenne_twister.hpp"

int DiceParam::roll() const
{
    return rnd::dice(rolls, sides) + plus;
}

int Range::roll() const
{
    return rnd::range(min, max);
}

bool Fraction::roll() const
{
    return rnd::fraction(num, den);
}

namespace rnd
{

namespace
{

MTRand mt_rand;

int roll(const int rolls, const int sides)
{
    if (sides <= 0)
    {
        return 0;
    }

    if (sides == 1)
    {
        return rolls * sides;
    }

    int result = 0;

    for (int i = 0; i < rolls; ++i)
    {
        result += mt_rand.randInt(sides - 1) + 1;
    }

    return result;
}

} // namespace

void seed(const unsigned long val)
{
    mt_rand = MTRand(val);
}

int dice(const int rolls, const int sides)
{
    return roll(rolls, sides);
}

bool coin_toss()
{
    return roll(1, 2) == 2;
}

bool fraction(const int numer, const int denom)
{
    // This function should never be called with a denominator less than one,
    // since it's unclear what e.g. "N times in -1" would mean.
    ASSERT(denom >= 1);

    // If the numerator is bigger than the denominator, it's likely a bug
    // (should something occur e.g. 5 times in 3 ???) - don't allow this...
    ASSERT(numer <= denom);

    // A negative numerator is of course nonsense
    ASSERT(numer >= 0);

    // If any of the rules above are broken on a release build, try to perform
    // the action that was *probably* intended.

    // NOTE: A numerator of 0 is always allowed (it simply means "no chance")

    if ((numer <= 0) || (denom <= 0))
    {
        return false;
    }

    if ((numer >= denom) || (denom == 1))
    {
        return true;
    }

    return roll(1, denom) <= numer;
}

bool one_in(const int N)
{
    return fraction(1, N);
}

int range(const int v1, const int v2)
{
    const int min = std::min(v1, v2);
    const int max = std::max(v1, v2);

    return min + roll(1, max - min + 1) - 1;
}

int percent()
{
    return roll(1, 100);
}

bool percent(const int pct_chance)
{
    return pct_chance >= roll(1, 100);
}

int weighted_choice(const std::vector<int> weights)
{
#ifndef NDEBUG
    for (const int weight : weights)
    {
        ASSERT(weight > 0);
    }
#endif // NDEBUG

    const int sum = std::accumulate(begin(weights), end(weights), 0);

    int rnd = rnd::range(0, sum - 1);

    for (size_t i = 0; i < weights.size(); ++i)
    {
        const int weight = weights[i];

        if (rnd < weight)
        {
            return i;
        }

        rnd -= weight;
    }

    // This point should never be reached
    ASSERT(false);

    return 0;
}

} // rnd
