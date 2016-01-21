#pragma once

#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <memory>

#define MAX_PROB_RESOLUTION 10000


#define MELEE_MAX_LEVEL 10
#define MELEE_BASE_DAMAGE 2
#define MELEE_BASE_PROB 0.80

#define RANGE_MAX_LEVEL 8
#define RANGE_BASE_DAMAGE 4
#define RANGE_BASE_PROB 0.60

#define HEAL_MAX_LEVEL 5
#define HEAL_BASE_HEAL 5
#define HEAL_BASE_PROB 0.90

static inline double cal_prob(double base, unsigned int level)
{
    return 1.0 - pow(1.0 - base, static_cast<double>(level));
}

static inline double drand()
{
    return static_cast<double>(rand() % MAX_PROB_RESOLUTION)/static_cast<double>(MAX_PROB_RESOLUTION);
}

static inline unsigned int cal_damage(unsigned int base, unsigned int level)
{
    return (base * (8 + level * level)) / 8;
}

/*
 * ****  ****  ****  ****  ****
 * 
 *       Attack Declairation
 * 
 * ****  ****  ****  ****  ****
 */

template<class P>
class Attack
{
protected:
    std::string d_ability_name;
    std::string d_status;
    unsigned int d_level;
public:
    Attack(std::string const &);
    Attack(Attack<P> const &);
    Attack(Attack<P> &&) = delete;
    Attack<P> const & operator=(Attack<P> const &) = delete;
    Attack<P> const & operator=(Attack<P> &&) = delete;
    virtual Attack<P> * clone() const = 0;
    virtual void levelup();
    virtual bool perform(P) const = 0;
    unsigned int get_level() const;
    std::string get_ability_name() const;
    std::string get_status() const;
};

template<class P>
std::ostream & operator<<(std::ostream & os, Attack<P> const & attack)
{
    os << attack.get_ability_name() << " (lvl " << attack.get_level() << ")";
    return os;
}

template<class P>
class MeleeAttack : public Attack<P>
{
    unsigned int d_damage;
    double d_probability;
public:
    MeleeAttack();
    MeleeAttack(MeleeAttack<P> const &);
    virtual Attack<P> * clone() const;
    virtual void levelup();
    virtual bool perform(P) const;
};

template<class P>
class RangeAttack : public Attack<P>
{
    unsigned int d_damage;
    double d_probability;
public:
    RangeAttack();
    RangeAttack(RangeAttack<P> const &);
    virtual Attack<P> * clone() const;
    virtual void levelup();
    virtual bool perform(P) const;
};

template<class P>
class HealingAttack : public Attack<P>
{
    unsigned int d_heal;
    double d_probability;
public:
    HealingAttack();
    HealingAttack(HealingAttack<P> const &);
    virtual Attack<P> * clone() const;
    virtual void levelup();
    virtual bool perform(P) const;
};

/*
 * ****  ****  ****  ****  ****
 * 
 *       Attack Definition
 * 
 * ****  ****  ****  ****  ****
 */

template<class P>
Attack<P>::Attack(std::string const & ability_name):
    d_ability_name(ability_name), d_status(""), d_level(1u) {}

template<class P>
Attack<P>::Attack(Attack<P> const & attack):
    d_ability_name(attack.d_ability_name), d_status(attack.d_status),
    d_level(attack.d_level) {}

template<class P>
void Attack<P>::levelup()
{
    d_level++;
}

template<class P>
unsigned int Attack<P>::get_level() const
{
    return d_level;
}

template<class P>
std::string Attack<P>::get_status() const
{
    return d_status;
}

/*
 * ****  ****  ****  ****  ****
 * 
 *    Melee Attack Definition
 * 
 * ****  ****  ****  ****  ****
 */

template<class P>
MeleeAttack<P>::MeleeAttack():
    Attack<P>(std::string("Melee")), d_damage(MELEE_BASE_DAMAGE),
    d_probability(MELEE_BASE_PROB) {}

template<class P>
MeleeAttack<P>::MeleeAttack(MeleeAttack<P> const & mattack):
    Attack<P>(static_cast<Attack<P>>(mattack)), d_damage(mattack.d_damage),
    d_probability(mattack.d_probability) {}

template<class P>
Attack<P> * MeleeAttack<P>::clone() const
{
    return new MeleeAttack<P>(* this);
}

template<class P>
void MeleeAttack<P>::levelup()
{
    if (Attack<P>::d_level >= MELEE_MAX_LEVEL) return;
    Attack<P>::levelup();
    d_damage = cal_damage(MELEE_BASE_DAMAGE, Attack<P>::d_level);
    d_probability = cal_prob(MELEE_BASE_PROB, Attack<P>::d_level);
}

template<class P>
bool MeleeAttack<P>::perform(P player_ptr) const
{
    if (d_probability >= drand())
    {
        // Attack sucessfull
        player_ptr->inventory() -= d_damage;
        Attack<P>::d_status = "hit";
        return true;
    }
    else
    {
        // Attack fail
        Attack<P>::d_status = "missed";
        return false;
    }
}

/*
 * ****  ****  ****  ****  ****
 * 
 *    Range Attack Definition
 * 
 * ****  ****  ****  ****  ****
 */

template<class P>
RangeAttack<P>::RangeAttack():
    Attack<P>(std::string("Range")), d_damage(RANGE_BASE_DAMAGE),
    d_probability(RANGE_BASE_PROB) {}

template<class P>
RangeAttack<P>::RangeAttack(RangeAttack<P> const & rattack):
    Attack<P>(static_cast<Attack<P>>(rattack)), d_damage(rattack.d_damage),
    d_probability(rattack.d_probability) {}

template<class P>
Attack<P> * RangeAttack<P>::clone() const
{
    return new RangeAttack<P>(* this);
}

template<class P>
void RangeAttack<P>::levelup()
{
    if (Attack<P>::d_level >= RANGE_MAX_LEVEL) return;
    Attack<P>::levelup();
    d_damage = cal_damage(RANGE_BASE_DAMAGE, Attack<P>::d_level);
    d_probability = cal_prob(RANGE_BASE_PROB, Attack<P>::d_level);
}

template<class P>
bool RangeAttack<P>::perform(P player_ptr) const
{
    if (d_probability >= drand())
    {
        // Attack sucessfull
        player_ptr->inventory() -= d_damage;
        Attack<P>::d_status = "hit";
        return true;
    }
    else
    {
        // Attack fail
        Attack<P>::d_status = "missed";
        return false;
    }
}

/*
 * ****  ****  ****  ****  ****
 * 
 *    Healing Attack Definition
 * 
 * ****  ****  ****  ****  ****
 */

template<class P>
HealingAttack<P>::HealingAttack():
    Attack<P>(std::string("Healing")), d_heal(HEAL_BASE_HEAL),
    d_probability(HEAL_BASE_PROB) {}

template<class P>
HealingAttack<P>::HealingAttack(HealingAttack<P> const & hattack):
    Attack<P>(static_cast<Attack<P>>(hattack)), d_heal(hattack.d_damage),
    d_probability(hattack.d_probability) {}

template<class P>
Attack<P> * HealingAttack<P>::clone() const
{
    return new HealingAttack<P>(* this);
}

template<class P>
void HealingAttack<P>::levelup()
{
    if (Attack<P>::d_level >= HEAL_MAX_LEVEL) return;
    Attack<P>::levelup();
    d_heal = cal_damage(HEAL_BASE_HEAL, Attack<P>::d_level);
    d_probability = cal_prob(HEAL_BASE_PROB, Attack<P>::d_level);
}

template<class P>
bool HealingAttack<P>::perform(P player_ptr) const
{
    if (d_probability >= drand())
    {
        // Attack sucessfull
        player_ptr->inventory() += d_heal;
        Attack<P>::d_status = "hit";
        return true;
    }
    else
    {
        // Attack fail
        Attack<P>::d_status = "missed";
        return false;
    }
}


template<class P>
class AttackSet
{
    std::shared_ptr<MeleeAttack<P>> melee_ptr;
    std::shared_ptr<RangeAttack<P>> range_ptr;
    std::shared_ptr<HealingAttack<P>> heal_ptr;

public:
    AttackSet();
    AttackSet(AttackSet const &);

    std::shared_ptr<MeleeAttack<P>> melee();
    std::shared_ptr<RangeAttack<P>> range();
    std::shared_ptr<HealingAttack<P>> heal();

    void new_melee();
    void new_range();
    void new_heal();

    // friend std::ostream& operator<<(std::ostream& os, AttackSet const &);
};

template<class P>
AttackSet<P>::AttackSet() {}

template<class P>
AttackSet<P>::AttackSet(AttackSet<P> const & attack_set)
{
    if (attack_set.melee_ptr)
        melee_ptr.reset(attack_set.melee_ptr->clone());
    if (attack_set.range_ptr)
        range_ptr.reset(attack_set.range_ptr->clone());
    if (attack_set.heal_ptr)
        heal_ptr.reset(attack_set.heal_ptr->clone());
}

template<class P>
std::shared_ptr<MeleeAttack<P>> AttackSet<P>::melee()
{
    return melee_ptr;
}

template<class P>
std::shared_ptr<RangeAttack<P>> AttackSet<P>::range()
{
    return range_ptr;
}

template<class P>
std::shared_ptr<HealingAttack<P>> AttackSet<P>::heal()
{
    return heal_ptr;
}

template<class P>
void AttackSet<P>::new_melee()
{
    melee_ptr.reset(new MeleeAttack<P>());
}

template<class P>
void AttackSet<P>::new_range()
{
    range_ptr.reset(new RangeAttack<P>());
}

template<class P>
void AttackSet<P>::new_heal()
{
    heal_ptr.reset(new HealingAttack<P>());
}

template<class P>
std::ostream& operator<<(std::ostream& os, AttackSet<P> const & attack_set)
{
    unsigned int i = 1;

    if (attack_set.melee())
    {
        os << i++ << * attack_set.melee();
    }
    if (attack_set.range())
    {
        if (i != 1)
            os << std::endl;
        os << i++ << * attack_set.range();
    }
    if (attack_set.heal())
    {
        if (i != 1)
            os << std::endl;
        os << i++ << * attack_set.heal();
    }

    return os;
}
