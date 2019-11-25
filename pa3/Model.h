//
// Created by justi on 11/19/2019.
//

#ifndef PA3_MODEL_H
#define PA3_MODEL_H


#include "GameObject.h"
#include "Pokemon.h"
#include "View.h"

class Model {
private:
    Point2D pt1, pt2, pt3, pt4, pt5;
    int time;
    GameObject * object_ptrs[10];
    int num_objects;
    Pokemon * pokemon_ptrs[10];
    int num_pokemon;
    Pokemon * pokemon1;
    Pokemon * pokemon2;
    PokemonCenter * center_ptrs[10];
    int num_centers;
    PokemonCenter * center1;
    PokemonCenter * center2;
    PokemonGym * gym_ptrs[10];
    int num_gyms;
    PokemonGym * gym1;
    PokemonGym * gym2;
public:
    Model();
    ~Model();
    Pokemon * GetPokemonPtr(int id);
    PokemonCenter * GetPokemonCenterPtr(int id);
    PokemonGym * GetPokemonGymPtr(int id);
    bool Update();
    void Display(View& view);
    void ShowStatus();


};


#endif //PA3_MODEL_H
