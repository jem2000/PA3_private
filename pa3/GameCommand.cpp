//
// Created by justi on 11/19/2019.
//

#include "GameCommand.h"
#include <iostream>
using namespace std;

void GameCommand::DoMoveCommand(Model & model, int pokemon_id, Point2D p1)
{
    if (model.GetPokemonPtr(pokemon_id) == 0)
        cout << "Error: Please enter a valid command!" << endl;
    else {
        Pokemon *CurrentPokemon = model.GetPokemonPtr(pokemon_id);
        cout << "Moving " << CurrentPokemon->GetName() << " to " << p1 << "." << endl;
        CurrentPokemon->StartMoving(p1);
    }
}
void GameCommand::DoMoveToCenterCommand(Model & model, int pokemon_id, int center_id)
{
    if (model.GetPokemonPtr(pokemon_id) == 0)
        cout << "Error: Please enter a valid command!" << endl;
    else {
        Pokemon *CurrentPokemon = model.GetPokemonPtr(pokemon_id);
        PokemonCenter *CurrentCenter = model.GetPokemonCenterPtr(center_id);
        cout << "Moving " << CurrentPokemon->GetName() << " to " << CurrentCenter->GetId() << "." << endl;
        CurrentPokemon->StartMovingToCenter(CurrentCenter);
    }
}
void GameCommand::DoMoveToGymCommand(Model & model, int pokemon_id, int gym_id)
{
    if (model.GetPokemonPtr(pokemon_id) == 0)
        cout << "Error: Please enter a valid command!" << endl;
    else {
        Pokemon *CurrentPokemon = model.GetPokemonPtr(pokemon_id);
        PokemonGym *CurrentGym = model.GetPokemonGymPtr(gym_id);
        cout << "Moving " << CurrentPokemon->GetName() << " to " << CurrentGym->GetId() << endl;
        CurrentPokemon->StartMovingToGym(CurrentGym);
    }
}
void GameCommand::DoStopCommand(Model & model, int pokemon_id)
{
    if (model.GetPokemonPtr(pokemon_id) == 0)
        cout << "Error: Please enter a valid command!" << endl;
    else {
        Pokemon *CurrentPokemon = model.GetPokemonPtr(pokemon_id);
        cout << "Stopping " << CurrentPokemon->GetName() << "." << endl;
        CurrentPokemon->Stop();
    }
}
void GameCommand::DoTrainInGymCommand(Model & model, int pokemon_id, unsigned int training_units)
{
    if (model.GetPokemonPtr(pokemon_id) == 0)
        cout << "Error: Please enter a valid command!" << endl;
    else {
        Pokemon *CurrentPokemon = model.GetPokemonPtr(pokemon_id);
        cout << "Training " << CurrentPokemon->GetName() << "." << endl;
        CurrentPokemon->StartTraining(training_units);
    }
}
void GameCommand::DoRecoverInCenterCommand(Model& model, int pokemon_id, unsigned int stamina_points)
{
    if (model.GetPokemonPtr(pokemon_id) == 0)
        cout << "Error: Please enter a valid command!" << endl;
    else {
        Pokemon *CurrentPokemon = model.GetPokemonPtr(pokemon_id);
        cout << "Recovering " << CurrentPokemon->GetName() << "'s stamina" << endl;
        CurrentPokemon->StartRecoveringStamina(stamina_points);
    }
}

void GameCommand::DoGoCommand(Model& model, View& view)
{
    cout << "Advancing one tick." << endl;
    model.Update();
    model.ShowStatus();
    model.Display(view);
}
void GameCommand::DoRunCommand(Model& model, View& view)
{
    cout << "Advancing to next event" << endl;
    for (int i = 0; i < 5; i++)
    {
        if (!model.Update())
                model.Update();
    }
    model.ShowStatus();
    model.Display(view);
}
