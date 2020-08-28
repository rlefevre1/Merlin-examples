#ifndef A_STAR_TEST_H
#define A_STAR_TEST_H

#include <merlin-operational-research/merlin_a_star.hpp>

#include <vector>
using simple_map_t = std::vector<std::vector<short>>;

class LocationState: public ores::State
{
    protected:
        std::pair<int, int> map_size_;    // <X, Y>
        std::pair<int, int> position_;    // <X, Y>
        std::pair<int, int> destination_; // <X, Y>
        const simple_map_t * const map_;

        bool isRectangular() const;
        bool exists(int x, int y) const;
        bool isObstacle(int x, int y) const;

    public:
        LocationState(unsigned int posx, unsigned int posy, unsigned int destx, unsigned int desty, const simple_map_t & map);

        LocationState(const LocationState &) = delete;
        LocationState & operator=(const LocationState &) = delete;
        LocationState(LocationState &&) = delete;
        LocationState & operator=(LocationState &&) = delete;

        unsigned int X() const;
        unsigned int Y() const;

        friend bool operator==(const LocationState & lhs, const LocationState & rhs);
        friend bool operator!=(const LocationState & lhs, const LocationState & rhs);

        // INHERITED MEMBER FUNCTIONS
        bool isSolution() const override;
        std::list<State *> successors() const override;
        double h() const override;
        double k(const State * s) const override;
        bool equals(const State * s) const override;
};

#endif // A_STAR_TEST_H
