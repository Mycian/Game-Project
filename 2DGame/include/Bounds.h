#ifndef BOUNDS_H
#define BOUNDS_H
#include <vector>
#include <iostream>


class Bounds
{
    public:
        Bounds();
        virtual ~Bounds();
        bool checkCollision(int checkX, int checkY);
        int points;
        std::vector<int> x;
        std::vector<int> y;

    protected:

    private:
};

#endif // BOUNDS_H
