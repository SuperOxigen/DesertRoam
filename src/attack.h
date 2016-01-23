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

/*
 * ****  ****  ****  ****  ****
 * 
 * Helper Function Declairation
 * 
 * ****  ****  ****  ****  ****
 */

/*------------------------
 * Function: drand
 * Parameters: NONE
 * Returns: Random double [0.0,1.0)
 * Description:
 *     Generates a random double from
 *     0 (inclusive) and 1 (exclusive).
 *     Has a resolution as specified by
 *     MAX_PROB_RESOLUTION.
 *-----------------------*/
static inline double drand()
{
    return static_cast<double>(rand() % MAX_PROB_RESOLUTION)/static_cast<double>(MAX_PROB_RESOLUTION);
}

/*------------------------
 * Function: calc_prob
 * Parameters: base  - base probability
 *             level - level of compounding
 * Returns: decimal value of probability
 * Description:
 *     Calculates a probability that converges to
 *     1.0 as the level increases.
 *         p = 1.0 - (1.0 - b) ^ l
 *-----------------------*/
static inline double calc_prob(double base, unsigned int level)
{
    return 1.0 - pow(1.0 - base, static_cast<double>(level));
}

/*------------------------
 * Function: calc_damage
 * Parameters: base  - base damage
 *             level - level of compounding
 * Returns: integer of level's damgage
 * Description:
 *     Calaculates the damage that should be done
 *     for the attack level.
 *         d = b * (1 + 0.125 * l ^ 2)
 *-----------------------*/
static inline unsigned int calc_damage(unsigned int base, unsigned int level)
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

/*------------------------
 * Class: Attack (virtual/abstract)
 * Description:
 *     Represents an attack that can be
 *     performed on a pointer of type Ptr.
 *
 *     Intended to be overrided for a 
 *     specific attack type.
 *-----------------------*/
template<class Ptr>
class Attack
{
protected:
    std::string d_ability_name;
    std::string d_status;
    unsigned int d_level;
public:
    Attack(std::string const &);
    Attack(Attack<Ptr> const &);
    Attack(Attack<Ptr> &&) = delete;
    Attack<Ptr> const & operator=(Attack<Ptr> const &) = delete;
    Attack<Ptr> const & operator=(Attack<Ptr> &&) = delete;
    virtual Attack<Ptr> * clone() const = 0;
    virtual void levelup();
    virtual bool perform(Ptr) const = 0;
    unsigned int get_level() const;
    std::string get_ability_name() const;
    std::string get_status() const;
};

template<class Ptr>
std::ostream & operator<<(std::ostream & os, Attack<Ptr> const & attack)
{
    os << attack.get_ability_name() << " (lvl " << attack.get_level() << ")";
    return os;
}

template<class Ptr>
class MeleeAttack : public Attack<Ptr>
{
    unsigned int d_damage;
    double d_probability;
public:
    MeleeAttack();
    MeleeAttack(MeleeAttack<Ptr> const &);
    virtual Attack<Ptr> * clone() const;
    virtual void levelup();
    virtual bool perform(Ptr) const;
};

template<class Ptr>
class RangeAttack : public Attack<Ptr>
{
    unsigned int d_damage;
    double d_probability;
public:
    RangeAttack();
    RangeAttack(RangeAttack<Ptr> const &);
    virtual Attack<Ptr> * clone() const;
    virtual void levelup();
    virtual bool perform(Ptr) const;
};

template<class Ptr>
class HealingAttack : public Attack<Ptr>
{
    unsigned int d_heal;
    double d_probability;
public:
    HealingAttack();
    HealingAttack(HealingAttack<Ptr> const &);
    virtual Attack<Ptr> * clone() const;
    virtual void levelup();
    virtual bool perform(Ptr) const;
};

/*
 * ****  ****  ****  ****  ****
 * 
 *       Attack Definition
 * 
 * ****  ****  ****  ****  ****
 */

template<class Ptr>
Attack<Ptr>::Attack(std::string const & ability_name):
    d_ability_name(ability_name), d_status(""), d_level(1u) {}

template<class Ptr>
Attack<Ptr>::Attack(Attack<Ptr> const & attack):
    d_ability_name(attack.d_ability_name), d_status(attack.d_status),
    d_level(attack.d_level) {}

template<class Ptr>
void Attack<Ptr>::levelup()
{
    d_level++;
}

template<class Ptr>
unsigned int Attack<Ptr>::get_level() const
{
    return d_level;
}

template<class Ptr>
std::string Attack<Ptr>::get_status() const
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

template<class Ptr>
MeleeAttack<Ptr>::MeleeAttack():
    Attack<Ptr>(std::string("Melee")), d_damage(MELEE_BASE_DAMAGE),
    d_probability(MELEE_BASE_PROB) {}

template<class Ptr>
MeleeAttack<Ptr>::MeleeAttack(MeleeAttack<Ptr> const & mattack):
    Attack<Ptr>(static_cast<Attack<Ptr>>(mattack)), d_damage(mattack.d_damage),
    d_probability(mattack.d_probability) {}

template<class Ptr>
Attack<Ptr> * MeleeAttack<Ptr>::clone() const
{
    return new MeleeAttack<Ptr>(* this);
}

template<class Ptr>
void MeleeAttack<Ptr>::levelup()
{
    if (Attack<Ptr>::d_level >= MELEE_MAX_LEVEL) return;
    Attack<Ptr>::levelup();
    d_damage = calc_damage(MELEE_BASE_DAMAGE, Attack<Ptr>::d_level);
    d_probability = calc_prob(MELEE_BASE_PROB, Attack<Ptr>::d_level);
}

template<class Ptr>
bool MeleeAttack<Ptr>::perform(Ptr player_ptr) const
{
    if (d_probability >= drand())
    {
        // Attack sucessfull
        player_ptr->health() -= d_damage;
        Attack<Ptr>::d_status = "hit";
        return true;
    }
    else
    {
        // Attack fail
        Attack<Ptr>::d_status = "missed";
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

template<class Ptr>
RangeAttack<Ptr>::RangeAttack():
    Attack<Ptr>(std::string("Range")), d_damage(RANGE_BASE_DAMAGE),
    d_probability(RANGE_BASE_PROB) {}

template<class Ptr>
RangeAttack<Ptr>::RangeAttack(RangeAttack<Ptr> const & rattack):
    Attack<Ptr>(static_cast<Attack<Ptr>>(rattack)), d_damage(rattack.d_damage),
    d_probability(rattack.d_probability) {}

template<class Ptr>
Attack<Ptr> * RangeAttack<Ptr>::clone() const
{
    return new RangeAttack<Ptr>(* this);
}

template<class Ptr>
void RangeAttack<Ptr>::levelup()
{
    if (Attack<Ptr>::d_level >= RANGE_MAX_LEVEL) return;
    Attack<Ptr>::levelup();
    d_damage = calc_damage(RANGE_BASE_DAMAGE, Attack<Ptr>::d_level);
    d_probability = calc_prob(RANGE_BASE_PROB, Attack<Ptr>::d_level);
}

template<class Ptr>
bool RangeAttack<Ptr>::perform(Ptr player_ptr) const
{
    if (d_probability >= drand())
    {
        // Attack sucessfull
        player_ptr->health() -= d_damage;
        Attack<Ptr>::d_status = "hit";
        return true;
    }
    else
    {
        // Attack fail
        Attack<Ptr>::d_status = "missed";
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

template<class Ptr>
HealingAttack<Ptr>::HealingAttack():
    Attack<Ptr>(std::string("Healing")), d_heal(HEAL_BASE_HEAL),
    d_probability(HEAL_BASE_PROB) {}

template<class Ptr>
HealingAttack<Ptr>::HealingAttack(HealingAttack<Ptr> const & hattack):
    Attack<Ptr>(static_cast<Attack<Ptr>>(hattack)), d_heal(hattack.d_damage),
    d_probability(hattack.d_probability) {}

template<class Ptr>
Attack<Ptr> * HealingAttack<Ptr>::clone() const
{
    return new HealingAttack<Ptr>(* this);
}

template<class Ptr>
void HealingAttack<Ptr>::levelup()
{
    if (Attack<Ptr>::d_level >= HEAL_MAX_LEVEL) return;
    Attack<Ptr>::levelup();
    d_heal = calc_damage(HEAL_BASE_HEAL, Attack<Ptr>::d_level);
    d_probability = calc_prob(HEAL_BASE_PROB, Attack<Ptr>::d_level);
}

template<class Ptr>
bool HealingAttack<Ptr>::perform(Ptr player_ptr) const
{
    if (d_probability >= drand())
    {
        // Attack sucessfull
        player_ptr->health() += d_heal;
        Attack<Ptr>::d_status = "hit";
        return true;
    }
    else
    {
        // Attack fail
        Attack<Ptr>::d_status = "missed";
        return false;
    }
}


template<class Ptr>
class AttackSet
{
    std::shared_ptr<MeleeAttack<Ptr>> melee_ptr;
    std::shared_ptr<RangeAttack<Ptr>> range_ptr;
    std::shared_ptr<HealingAttack<Ptr>> heal_ptr;

public:
    AttackSet();
    AttackSet(AttackSet const &);

    std::shared_ptr<MeleeAttack<Ptr>> melee();
    std::shared_ptr<RangeAttack<Ptr>> range();
    std::shared_ptr<HealingAttack<Ptr>> heal();

    void new_melee();
    void new_range();
    void new_heal();

    // friend std::ostream& operator<<(std::ostream& os, AttackSet const &);
};

template<class Ptr>
AttackSet<Ptr>::AttackSet() {}

template<class Ptr>
AttackSet<Ptr>::AttackSet(AttackSet<Ptr> const & attack_set)
{
    if (attack_set.melee_ptr)
        melee_ptr.reset(attack_set.melee_ptr->clone());
    if (attack_set.range_ptr)
        range_ptr.reset(attack_set.range_ptr->clone());
    if (attack_set.heal_ptr)
        heal_ptr.reset(attack_set.heal_ptr->clone());
}

template<class Ptr>
std::shared_ptr<MeleeAttack<Ptr>> AttackSet<Ptr>::melee()
{
    return melee_ptr;
}

template<class Ptr>
std::shared_ptr<RangeAttack<Ptr>> AttackSet<Ptr>::range()
{
    return range_ptr;
}

template<class Ptr>
std::shared_ptr<HealingAttack<Ptr>> AttackSet<Ptr>::heal()
{
    return heal_ptr;
}

template<class Ptr>
void AttackSet<Ptr>::new_melee()
{
    melee_ptr.reset(new MeleeAttack<Ptr>());
}

template<class Ptr>
void AttackSet<Ptr>::new_range()
{
    range_ptr.reset(new RangeAttack<Ptr>());
}

template<class Ptr>
void AttackSet<Ptr>::new_heal()
{
    heal_ptr.reset(new HealingAttack<Ptr>());
}

template<class Ptr>
std::ostream& operator<<(std::ostream& os, AttackSet<Ptr> const & attack_set)
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
