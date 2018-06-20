//
// Created by dsalexan on 20/06/2018.
//

#ifndef PACMAN_PROJECT_RANDOM_H
#define PACMAN_PROJECT_RANDOM_H



class Random {

public:
    void seed();
    static void seed(int i);
    static int next(int nMax);
};

#endif //PACMAN_PROJECT_RANDOM_H
