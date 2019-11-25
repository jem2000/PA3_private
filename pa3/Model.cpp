//
// Created by justi on 11/19/2019.
//

#include "Pokemon.h"
#include "Model.h"
#include "View.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Model::Model() : object_ptrs(), pokemon_ptrs(), center_ptrs(), gym_ptrs()
{
    time = 0;

    pt1 = Point2D(1,5);
    pokemon1 = new Pokemon("Reuniclus", 1, 'P', 2, pt1);
    object_ptrs[0] = pokemon1;
    pokemon_ptrs[0] = pokemon1;

    pt2 = Point2D(10,1);
    pokemon2 = new Pokemon("Decidueye", 2, 'P', 1, pt2);
    object_ptrs[1] = pokemon2;
    pokemon_ptrs[1] = pokemon2;

    pt3 = Point2D(1,20);
    center1 = new PokemonCenter(1, 1, 100, pt3);
    object_ptrs[2] = center1;
    center_ptrs[0] = center1;

    pt4 = Point2D(10,20);
    center2 = new PokemonCenter(2, 2, 200, pt4);
    object_ptrs[3] = center2;
    center_ptrs[1] = center2;

    gym1 = new PokemonGym();
    object_ptrs[4] = gym1;
    gym_ptrs[0] = gym1;

    pt5 = Point2D(5,5);
    gym2 = new PokemonGym(150, 3, 3.25, 20, 2, pt5);
    object_ptrs[5] = gym2;
    gym_ptrs[1] = gym2;

    num_objects = 6;
    num_pokemon = 2;
    num_centers = 2;
    num_gyms = 2;

    cout << "Model default constructed" << endl;

}
Model::~Model()
{
    delete pokemon1;
    delete pokemon2;
    delete center1;
    delete center2;
    delete gym1;
    delete gym2;
    cout << "Model destructed" << endl;


}
Pokemon * Model::GetPokemonPtr(int id)
{
    for (int i = 0; i <= num_pokemon; i++) {
        if (id == pokemon_ptrs[i]->GetId())
            return pokemon_ptrs[i];
    }
    return 0;
}
PokemonCenter * Model::GetPokemonCenterPtr(int id)
{
    for (int i = 0; i <= num_centers; i++) {
        if (id == center_ptrs[i]->GetId())
            return center_ptrs[i];
    }
    return 0;
}
PokemonGym * Model::GetPokemonGymPtr(int id)
{
    for (int i = 0; i < num_gyms; i++) {
        if (id == gym_ptrs[i]->GetId())
            return gym_ptrs[i];
    }
    return 0;
}
bool Model::Update() {
    time++;
    bool hasWon = true;
    bool hasLost = true;
    for (int i = 0; i < num_gyms; i++) {
        if (!gym_ptrs[i]->IsBeaten())
            hasWon = false;
    }
    for (int i = 0; i < num_pokemon; i++) {
        if (!pokemon_ptrs[i]->IsExhausted())
            hasLost = false;
    }
    if (hasWon) {
        cout << "GAME OVER: You win! All Pokemon Gyms beaten!" << endl;
        exit(EXIT_SUCCESS);
    }
    if (hasLost) {
        cout << "GAME OVER: You lose! All of your Pokemon are exhausted!" << endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_objects; i++) {
        if (object_ptrs[i]->Update())
            return true;
    }
}

void Model::Display(View& view)
{
    cout << "Time: " << time << endl;
    view.clear();
    for (int i = 0; i < num_objects; i++)
        view.Plot(object_ptrs[i]);
    view.Draw();
}
void Model::ShowStatus()
{
for (int i = 0; i < num_pokemon; i++)
    pokemon_ptrs[i]->ShowStatus();
for (int i = 0; i < num_centers; i++)
    center_ptrs[i]->ShowStatus();
for (int i = 0; i < num_gyms; i++)
    gym_ptrs[i]->ShowStatus();
}