#pragma once

#include <iostream>

#define SMALL_BAR_TICKS 8
#define MEDIUM_BAR_TICKS 12
#define LARGE_BAR_TICKS 25

class StatBar
{
public:
    enum BarType { NUMBER, FRACTION, SMALL, MEDIUM, LARGE };
private:
    unsigned int d_value;
    unsigned int d_max_value;
    BarType d_bar_type;
public:
    StatBar(unsigned int);
    StatBar(unsigned int, unsigned int);
    explicit operator bool() const;
    explicit operator int() const;
    unsigned int operator+=(unsigned int);
    unsigned int operator-=(unsigned int);
    unsigned int operator=(unsigned int);
    bool is_full() const;
    void fill();
    unsigned int get_value() const;
    void set_value(unsigned int);
    unsigned int get_max_value() const;
    void set_max_value(unsigned int);
    BarType get_bar_type() const;
    void set_bar_type(BarType);
    bool operator==(StatBar const &) const;
    friend std::ostream& operator<<(std::ostream&, StatBar const &);
};
