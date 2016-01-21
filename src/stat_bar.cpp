#include "stat_bar.h"

using std::ostream;
using std::endl;

StatBar::StatBar(unsigned int max):
    d_value(max), d_max_value(max), d_bar_type(NUMBER) {}

StatBar::StatBar(unsigned int value, unsigned int max):
    d_value(value), d_max_value(max), d_bar_type(NUMBER) {}

StatBar::operator int () const
{
    return d_value;
}

StatBar::operator bool() const
{
    return d_value != 0;
}

unsigned int StatBar::operator+=(unsigned int value)
{
    d_value = value;
    if (d_value > d_max_value)
        d_value = d_max_value;
    return d_value;
}

unsigned int StatBar::operator-=(unsigned int value)
{
    unsigned int cur_value = d_value - value;
    if (cur_value > d_value)
        d_value = 0;
    else
        d_value = cur_value;

    return d_value;
}

unsigned int StatBar::operator=(unsigned int value)
{
    set_value(value);

    return value;
}

bool StatBar::is_full() const
{
    return d_value == d_max_value;
}

void StatBar::fill()
{
    d_value = d_max_value;
}

unsigned int StatBar::get_value() const
{
    return d_value;
}

void StatBar::set_value(unsigned int value)
{
    if (value > d_max_value)
        d_value = d_max_value;
    else
        d_value = value;
}

unsigned int StatBar::get_max_value() const
{
    return d_max_value;
}

void StatBar::set_max_value(unsigned int max_value)
{
    d_max_value = max_value;
}

StatBar::BarType StatBar::get_bar_type() const
{
    return d_bar_type;
}

void StatBar::set_bar_type(StatBar::BarType bar_type)
{
    d_bar_type = bar_type;
}

bool StatBar::operator==(StatBar const & stat_bar) const
{
    return (d_value == stat_bar.d_value &&
            d_max_value == stat_bar.d_max_value);
}

ostream & operator<<(ostream & os, StatBar const & stat_bar)
{
    size_t n = 0;
    switch (stat_bar.d_bar_type)
    {
        case StatBar::NUMBER:
            os << stat_bar.get_value();
            break;
        case StatBar::FRACTION:
            os << stat_bar.get_value();
            os << "/" << stat_bar.get_max_value();
            break;
        case StatBar::SMALL:
            n = SMALL_BAR_TICKS;
            break;
        case StatBar::MEDIUM:
            n = MEDIUM_BAR_TICKS;
            break;
        case StatBar::LARGE:
            n = LARGE_BAR_TICKS;
            break;
    }

    if (n)
    {
        os << "[";
        size_t bars = stat_bar.get_value() * n / stat_bar.get_max_value();
        size_t i;
        for (i = 0; i < n - bars; i++)
            os << " ";
        for (; i < n; i++)
            os << "#";
        os << "]";
    }

    return os;
}

