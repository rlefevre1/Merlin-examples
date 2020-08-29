#include "a_star_example.hpp"

#include <cmath>

LocationState::LocationState(unsigned int posx, unsigned int posy,
                             unsigned int destx, unsigned int desty,
                             const simple_map_t & map) : position_{posx, posy},
                                                         destination_{destx, desty},
                                                         map_(&map)
{
    if(map_->empty())
        throw std::invalid_argument("[Error] LocationState::LocationState() - The given map is empty.");
    if(!isRectangular())
        throw std::invalid_argument("[Error] LocationState::LocationState() - The given map is ill formed (empty or not rectangular).");

    map_size_  = {(*map_)[0].size(), map_->size()};

    if(!exists(position_.first, position_.second))
        throw std::domain_error("[Error] LocationState::LocationState() - The given position is outside of the map.");
    if(!exists(destination_.first, destination_.second))
        throw std::domain_error("[Error] LocationState::LocationState() - The given destination is outside of the map.");
}

bool LocationState::isRectangular() const
{
    if(!map_->empty())
    {
        bool valid(true);
        std::size_t s = (*map_)[0].size();

        if(s == 0)
            valid = false;

        for(std::size_t i = 1; valid && i < map_->size(); ++i)
        {
            if((*map_)[i].size() != s)
                valid = false;
        }

        return valid;
    }
    else
        return false;
}
bool LocationState::exists(int x, int y) const
{
    return (x >= 0 && y >= 0 && x < map_size_.first && y < map_size_.second);
}
bool LocationState::isObstacle(int x, int y) const
{
    // 0: Obstacle, otherwise: Road
    if(exists(x, y))
        return (*map_)[static_cast<unsigned int>(y)][static_cast<unsigned int>(x)] == 0;
    else
        return true;
}

unsigned int LocationState::X() const
{
    return static_cast<unsigned int>(position_.first);
}
unsigned int LocationState::Y() const
{
    return static_cast<unsigned int>(position_.second);
}

bool operator==(const LocationState & lhs, const LocationState & rhs)
{
    return (lhs.position_==rhs.position_ && lhs.destination_==rhs.destination_ && lhs.map_==rhs.map_);
}
bool operator!=(const LocationState & lhs, const LocationState & rhs)
{
    return !(lhs == rhs);
}

bool LocationState::isSolution() const
{
    return (position_ == destination_);
}
std::list<merl::AStar::State *> LocationState::successors() const
{
    std::list<State*> neighbours;

    for(int dx = -1; dx <= 1; ++dx)
    {
        for(int dy = -1; dy <= 1; ++dy)
        {
            if(!(dx == 0 && dy == 0) && !isObstacle(position_.first + dx, position_.second + dy))
            {
                LocationState * ls = new LocationState(static_cast<unsigned int>(position_.first+dx), static_cast<unsigned int>(position_.second+dy),
                                                       static_cast<unsigned int>(destination_.first), static_cast<unsigned int>(destination_.second),
                                                       *map_);
                neighbours.push_back(ls);
            }
        }
    }

    return neighbours;
}
double LocationState::h() const
{
    return std::sqrt((destination_.first-position_.first)*(destination_.first-position_.first) + (destination_.second-position_.second)*(destination_.second-position_.second));
}
double LocationState::k(const merl::AStar::State * s) const
{
    const LocationState * ls = dynamic_cast<const LocationState *>(s);
    return std::sqrt((ls->position_.first-position_.first)*(ls->position_.first-position_.first) + (ls->position_.second-position_.second)*(ls->position_.second-position_.second));
}
bool LocationState::equals(const merl::AStar::State * s) const
{
    const LocationState * ls = dynamic_cast<const LocationState *>(s);
    return (*ls == *this);
}
