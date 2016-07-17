#ifndef RL_UTILS_H
#define RL_UTILS_H

#include <vector>
#include <string>
#include <iostream>

// This header must be supplied by the "user" project, and contain some
// necessary symbols such as "map_w" and "map_h".
#include "global.hpp"

//------------------------------------------------------------------------
// Trace level
//-----------------------------------------------------------------------------
// Lvl of TRACE output in debug mode
// 0 : Disabled
// 1 : Standard
// 2 : Verbose
#ifndef TRACE_LVL

#define TRACE_LVL 1

#endif // TRACE_LVL

//-----------------------------------------------------------------------------
// Custom trace output and assert functionality
//-----------------------------------------------------------------------------
#ifdef NDEBUG // Release mode

#define ASSERT(check)

#define TRACE                     if (1) ; else std::cerr
#define TRACE_FUNC_BEGIN          if (1) ; else std::cerr
#define TRACE_FUNC_END            if (1) ; else std::cerr
#define TRACE_VERBOSE             if (1) ; else std::cerr
#define TRACE_FUNC_BEGIN_VERBOSE  if (1) ; else std::cerr
#define TRACE_FUNC_END_VERBOSE    if (1) ; else std::cerr

#else // Debug mode

#define ASSERT(check) \
    do_not_call::assert_impl(check, #check, __FILE__, __LINE__, __func__)

#define TRACE if (TRACE_LVL < 1) ; else \
    std::cerr \
    << std::endl \
    << __FILE__ << ", " \
    << __LINE__ << ", " \
    << __func__ << "():" \
    << std::endl

#define TRACE_FUNC_BEGIN if (TRACE_LVL < 1) ; else \
    std::cerr \
    << std::endl \
    << __FILE__ << ", " \
    << __LINE__ << ", " \
    << __func__ << "()..." \
    << std::endl

#define TRACE_FUNC_END if (TRACE_LVL < 1) ; else \
    std::cerr \
    << std::endl \
    << __FILE__ << ", " \
    << __LINE__ << ", " \
    << __func__ << "() [DONE]" \
    << std::endl

#define TRACE_VERBOSE             if (TRACE_LVL < 2) ; else TRACE
#define TRACE_FUNC_BEGIN_VERBOSE  if (TRACE_LVL < 2) ; else TRACE_FUNC_BEGIN
#define TRACE_FUNC_END_VERBOSE    if (TRACE_LVL < 2) ; else TRACE_FUNC_END

#endif // NDEBUG

//-----------------------------------------------------------------------------
// Custom assert
// NOTE: Never call this function directly, use "ASSERT" macro above
//-----------------------------------------------------------------------------
namespace do_not_call
{

void assert_impl(const bool check,
                 const char* check_str,
                 const char* file,
                 const int line,
                 const char* func);

}

//-----------------------------------------------------------------------------
// Geometry
//-----------------------------------------------------------------------------
class P
{
public:
    P() :
        x(0),
        y(0) {}

    P(const int x, const int y) :
        x(x),
        y(y) {}

    P(const P& p) :
        x(p.x),
        y(p.y) {}

    P(const int v) :
        x(v),
        y(v) {}

    P& operator=(const P& p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }

    P& operator/=(const int v)
    {
        x /= v;
        y /= v;
        return *this;
    }

    P& operator+=(const P& p)
    {
        x += p.x;
        y += p.y;
        return *this;
    }

    P& operator-=(const P& p)
    {
        x -= p.x;
        y -= p.y;
        return *this;
    }

    P& operator++()
    {
        ++x;
        ++y;
        return *this;
    }

    P& operator--()
    {
        --x;
        --y;
        return *this;
    }

    P operator+(const P& p) const
    {
        return P(x + p.x, y + p.y);
    }

    P operator+(const int  v) const
    {
        return P(x + v, y + v);
    }

    P operator-(const P& p) const
    {
        return P(x - p.x, y - p.y);
    }

    P operator-(const int v) const
    {
        return P(x - v, y - v);
    }

    P operator/(const int  v) const
    {
        return P(x / v, y / v);
    }

    P operator/(const P& p) const
    {
        return P(x / p.x, y / p.y);
    }

    P operator*(const int v) const
    {
        return P(x * v, y * v);
    }

    P operator*(const P& p) const
    {
        return P(x * p.x, y * p.y);
    }

    bool operator==(const P& p) const
    {
        return x == p.x && y == p.y;
    }

    bool operator!=(const P& p) const
    {
        return x != p.x || y != p.y;
    }

    bool operator!=(const int v) const
    {
        return x != v || y != v;
    }

    bool operator>(const P& p) const
    {
        return x > p.x && y > p.y;
    }

    bool operator>(const int v) const
    {
        return x > v && y > v;
    }

    bool operator<(const P& p) const
    {
        return x < p.x && y < p.y;
    }

    bool operator<(const int v) const
    {
        return x < v && y < v;
    }

    bool operator>=(const P& p) const
    {
        return x >= p.x && y >= p.y;
    }

    bool operator>=(const int v) const
    {
        return x >= v && y >= v;
    }

    bool operator<=(const P& p) const
    {
        return x <= p.x && y <= p.y;
    }

    bool operator<=(const int  v) const
    {
        return x <= v && y <= v;
    }

    P signs() const
    {
        return P(x == 0 ? 0 : x > 0 ? 1 : -1,
                 y == 0 ? 0 : y > 0 ? 1 : -1);
    }

    void set(const int x_, const int y_)
    {
        x = x_;
        y = y_;
    }

    void set(const P& p)
    {
        x = p.x;
        y = p.y;
    }

    void swap(P& p)
    {
        P tmp(p);
        p = *this; set(tmp);
    }

    int x, y;
};

class R
{
public:
    R() :
        p0(P()),
        p1(P()) {}

    R(const P& p0, const P& p1) :
        p0(p0),
        p1(p1) {}

    R(const int x0, const int y0, const int x1, const int y1) :
        p0(P(x0, y0)),
        p1(P(x1, y1)) {}

    R(const R& r) :
        p0(r.p0),
        p1(r.p1) {}

    int w() const
    {
        return p1.x - p0.x + 1;
    }

    int h() const
    {
        return p1.y - p0.y + 1;
    }

    P dims() const
    {
        return P(w(), h());
    }

    int min_dim() const
    {
        return std::min(w(), h());
    }

    int max_dim() const
    {
        return std::max(w(), h());
    }

    P center() const
    {
        return ((p1 + p0) / 2);
    }

    bool is_p_inside(const P& p) const
    {
        return p >= p0 &&
               p <= p1;
    }

    R& operator+=(const P& p)
    {
        p0 += p;
        p1 += p;
        return *this;
    }

    R& operator-=(const P& p)
    {
        p0 -= p;
        p1 -= p;
        return *this;
    }

    // Useful for e.g. converting map cell dimensions to pixel dimensions
    R operator*(const P& p)
    {
        return R(p0 * p, p1 * p);
    }

    P p0;
    P p1;
};

struct Pos_val
{
    Pos_val() :
        pos(P()),
        val(-1) {}

    Pos_val(const P& pos_, const int val_) :
        pos     (pos_),
        val     (val_) {}

    Pos_val(const Pos_val& o) :
        pos     (o.pos),
        val     (o.val) {}

    P pos;
    int val;
};

//-----------------------------------------------------------------------------
// Utility functionality for working with directions and offsets
//-----------------------------------------------------------------------------
enum class Dir
{
    down_left   = 1,
    down        = 2,
    down_right  = 3,
    left        = 4,
    center      = 5,
    right       = 6,
    up_left     = 7,
    up          = 8,
    up_right    = 9,
    END
};

namespace dir_utils
{

const std::vector<P> cardinal_list
{
    P(-1,  0),
    P( 1,  0),
    P( 0, -1),
    P( 0,  1)
};

const std::vector<P> dir_list
{
    P(-1,  0),
    P( 1,  0),
    P( 0, -1),
    P( 0,  1),
    P(-1, -1),
    P(-1,  1),
    P( 1, -1),
    P( 1,  1)
};

const std::vector<P> dir_list_w_center
{
    P( 0,  0),
    P(-1,  0),
    P( 1,  0),
    P( 0, -1),
    P( 0,  1),
    P(-1, -1),
    P(-1,  1),
    P( 1, -1),
    P( 1,  1)
};

Dir dir(const P& offset_values);

P offset(const Dir dir);

P rnd_adj_pos(const P& origin, const bool is_center_allowed);

void compass_dir_name(const P& from_pos,
                      const P& to_pos,
                      std::string& dst);

void compass_dir_name(const Dir dir, std::string& dst);

void compass_dir_name(const P& offs, std::string& dst);

} // dir_utils

//-----------------------------------------------------------------------------
// Types for random number generation
//-----------------------------------------------------------------------------
struct Dice_param
{
    Dice_param() :
        rolls   (0),
        sides   (0),
        plus    (0) {}

    Dice_param(const int rolls, const int sides, const int plus = 0) :
        rolls   (rolls),
        sides   (sides),
        plus    (plus) {}

    Dice_param(const Dice_param& other) :
        rolls   (other.rolls),
        sides   (other.sides),
        plus    (other.plus) {}

    Dice_param& operator=(const Dice_param& other)
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

//-----------------------------------------------------------------------------
// Random number generation
//-----------------------------------------------------------------------------
namespace rnd
{

// NOTE: If no parameters are passed to the MTRand constructor, it will be seeded with current time.
// Seeding it manually is only necessary if seed should be controlled.
void seed(const unsigned long val);

// If not called with a positive non-zero number of sides, this will always return zero.
int dice(const int rolls, const int sides);

bool coin_toss();

bool fraction(const int numer, const int denom);

bool one_in(const int N);

// Can be called with any range (positive or negative), V2 does *not* have to be bigger than V1.
int range(const int v1, const int v2);

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

namespace floodfill
{

void run(const P& p0,
         const bool blocked[map_w][map_h],
         int out[map_w][map_h],
         int travel_lmt = -1,
         const P& p1 = P(-1, -1),
         const bool allow_diagonal = true);

} // floodfill

namespace pathfind
{

//-----------------------------------------------------------------------------
// The path goes from target to origin, not including the origin.
//
// "randomize_steps", when true, for each step if there are multiple valid
// (nearer) choices, pick one at random. Otherwise iterate over a predefined
// list of offsets until a valid step is found. The second way is more
// optimized and is the default behavior (best for e.g. AI), while the
// randomized method can produces nicer results in some cases (e.g. corridors).
//-----------------------------------------------------------------------------
void run(const P& p0,                           // Origin
         const P& p1,                           // Target
         const bool blocked[map_h][map_h],      // Blocked cells
         std::vector<P>& out,                   // Result
         const bool allow_diagonal = true,      // Cardinals only?
         const bool randomize_steps = false);   // See above

} // pathfind

enum class Time_type
{
    year,
    month,
    day,
    hour,
    minute,
    second
};

struct Time_data
{
    Time_data() :
        year_   (0),
        month_  (0),
        day_    (0),
        hour_   (0),
        minute_ (0),
        second_ (0) {}

    Time_data(int year,
              int month,
              int day,
              int hour,
              int minute,
              int second) :
        year_   (year),
        month_  (month),
        day_    (day),
        hour_   (hour),
        minute_ (minute),
        second_ (second) {}

    std::string time_str(const Time_type lowest,
                         const bool add_separators) const;

    int year_, month_, day_, hour_, minute_, second_;
};

//-----------------------------------------------------------------------------
// Misc utils
//-----------------------------------------------------------------------------
void set_constr_in_range(const int min,
                         int& val,
                         const int max);

void set_constr_in_range(const double min,
                         double& val,
                         const double max);

int constr_in_range(const int min,
                    const int val,
                    const int max);

int constr_in_range(const double min,
                    const double val,
                    const double max);

// Takes a boolean 2d array of given size, and populates a vector with positions matching the value
// to store (true/false). This can for example be useful if you have a parsed map of blocked and
// free cells, and you want a list of free cells to (randomly) select from.
void to_vec(const bool* array2,
            const bool value_to_store,
            const int w,
            const int h,
            std::vector<P>& out);

bool is_pos_inside(const P& pos, const R& area);

bool is_area_inside(const R& inner,
                    const R& outer,
                    const bool count_equal_as_inside);

bool is_pos_adj(const P& pos1,
                const P& pos2,
                const bool count_same_cell_as_adj);

P closest_pos(const P& p, const std::vector<P>& positions);

// Distance as the king moves in chess
// The distance between (x0, y0) and (x1, y1) is defined as max(|x1 - x0|, |y1 - y0|).
// This is typically the model used for movement in roguelikes.
int king_dist(const int x0,
              const int y0,
              const int x1,
              const int y1);

int king_dist(const P& p0, const P& p1);

// Taxicab distance - also called "rectilinear distance", "Manhattan distance", etc.
// The distance between (x0, y0) and (x1, y1) is defined as |x1 - x0| + |y1 - y0|.
int taxi_dist(const P& p0, const P& p1);

bool is_val_in_range(const int v, const Range range);

Time_data current_time();

std::string to_str(const int IN);

int to_int(const std::string& in);

#endif // RL_UTILS_H
