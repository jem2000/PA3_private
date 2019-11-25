//
// Created by justi on 11/11/2019.
//

#include "Pokemon.h"
#include <iostream>
#include <cmath>
#include "Point2D.h"
#include "Vector2D.h"
#include <cstdlib>

using namespace std;


Pokemon::Pokemon()
{
    speed = 5;
    cout << "Pokemon default constructed." << endl;
    is_in_gym = false;
    is_in_center = false;
    stamina = 20;
    experience_points = 0;
    pokemon_dollars = 0;
    training_units_to_buy = 0;
    stamina_points_to_buy = 0;
    current_center = 0;
    current_gym = 0;

}
Pokemon::Pokemon(char in_code)
{
    speed = 5;
    display_code = in_code;
    cout << "Pokemon constructed" << endl;
    is_in_gym = false;
    is_in_center = false;
    stamina = 20;
    experience_points = 0;
    pokemon_dollars = 0;
    training_units_to_buy = 0;
    stamina_points_to_buy = 0;
    current_center = 0;
    current_gym = 0;
}
Pokemon::Pokemon(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc)
{
    speed = in_speed;
    name = in_name;
    location = in_loc;
    id_num = in_id;
    display_code = in_code;
    cout << "Pokemon Constructed" << endl;
    is_in_gym = false;
    is_in_center = false;
    stamina = 20;
    experience_points = 0;
    pokemon_dollars = 0;
    training_units_to_buy = 0;
    stamina_points_to_buy = 0;
    current_center = 0;
    current_gym = 0;
}
void Pokemon::StartMoving(Point2D dest)
{
    if (dest.x == location.y && dest.y == location.y)
        cout << display_code << id_num << " I'm already there. See?" << endl;
    else if (state == EXHAUSTED)
        cout << display_code << id_num << "): I am exhausted. I may move but you cannot see me." << endl;
    else
    {
        SetupDestination(dest);
        state = MOVING;
        cout << display_code << id_num << " On my way." << endl;
    }

}
void Pokemon::StartMovingToCenter(PokemonCenter* center)
{
    current_center = center;
    if (state == IN_CENTER)
        cout << display_code << id_num << " I am already at the Pokemon Center!" << endl;
    else if (state == EXHAUSTED)
        cout << display_code << id_num << "): I am exhausted. I may move but you cannot see me." << endl;
    else
    {
        SetupDestination(current_center->GetLocation());
        state = MOVING_TO_CENTER;
        cout << display_code << id_num << " On my way to center." << endl;
    }
}
void Pokemon::StartMovingToGym(PokemonGym* gym)
{
    current_gym = gym;
    if (state == IN_GYM)
        cout << display_code << id_num << " I am already at the Pokemon Gym!" << endl;
    else if (state == EXHAUSTED)
        cout << display_code << id_num << ": I am exhausted so I shouldn't be going to the gym." << endl;
    else
    {
        SetupDestination(current_gym->GetLocation());
        state = MOVING_TO_GYM;
        cout << display_code << id_num << " On my way to gym." << endl;
    }
}
void Pokemon::StartTraining(unsigned int num_training_units)
{
    if (state == EXHAUSTED)
        cout << display_code << id_num << ": I am exhausted so no more training for me..." << endl;
    else if (!is_in_gym)
        cout << display_code << id_num << " I can only train in a Pokemon Gym!" << endl;
    else if (!current_gym->IsAbleToTrain(num_training_units, pokemon_dollars, stamina))
    {
        cout << display_code << id_num << ": Not enough stamina and/or money for training" << endl;
    }
    else if (state == BEATEN)
    {
        cout << display_code << id_num << "): Cannot train! This Pokemon Gym is already beaten!" << endl;
    }
    else
    {
        state = TRAINING_IN_GYM;
        cout << display_code << id_num << ": Started to train at Pokemon Gym " << current_gym->GetId() << " with " << num_training_units << " training units" << endl;
        if (num_training_units < current_gym->GetNumTrainingUnitsRemaining())
                training_units_to_buy = num_training_units;
        else
            training_units_to_buy = current_gym->GetNumTrainingUnitsRemaining();
    }
}
void Pokemon::StartRecoveringStamina(unsigned int num_stamina_points)
{
    if (state == NO_STAMINA_POINTS_AVAILABLE)
        cout << display_code << id_num << " Cannot recover! No stamina points remaining in this Pokemon Center" << endl;
    else if (state != IN_CENTER)
        cout << display_code << id_num << ": I can only recover stamina at a Pokemon Center!" << endl;
    else if (pokemon_dollars < current_center->getStaminaCost() * num_stamina_points)
        cout << display_code << id_num << " Not enough money to recover stamina." << endl;
    else if (stamina_points_to_buy == 1)
        cout << display_code << id_num << " Started recovering 1 stamina point at Pokemon Center " << current_center->GetId() << endl;
    else {
        state = RECOVERING_STAMINA;
        cout << display_code << id_num << " Started recovering " << num_stamina_points << " stamina points at Pokemon Center " << current_center->GetId() << endl;
        if (num_stamina_points < current_center->GetNumStaminaPointsRemaining())
            stamina_points_to_buy = num_stamina_points;
        else
            stamina_points_to_buy = current_center->GetNumStaminaPointsRemaining();
    }
}
void Pokemon::Stop()
{
    state = STOPPED;
    cout << display_code << id_num << ": Stopping." << endl;
}
bool Pokemon::IsExhausted()
{
    return stamina == 0;
}
bool Pokemon::ShouldBeVisible()
{
    return state != EXHAUSTED;
}
void Pokemon::ShowStatus()
{
    cout << name << " status: ";
    GameObject::ShowStatus();

    switch (state)
    {
        case STOPPED:
            cout << "stopped" << endl;
            cout << "   Stamina: " << stamina << endl;
            cout << "   Pokemon Dollars: " << pokemon_dollars << endl;
            cout << "   Experience Points: " << experience_points << endl;
            break;
        case MOVING:
            cout << "moving at a speed of " << speed << " to destination " << destination << " at each step of "  << delta << "." << endl;
            cout << "   Stamina: " << stamina << endl;
            cout << "   Pokemon Dollars: " << pokemon_dollars << endl;
            cout << "   Experience Points: " << experience_points << endl;
            break;
        case MOVING_TO_CENTER:
            cout << "heading to Pokemon Center " << current_center->GetId() << " at a speed of " << speed << " at each step of " << delta << "." << endl;
            cout << "   Stamina: " << stamina << endl;
            cout << "   Pokemon Dollars: " << pokemon_dollars << endl;
            cout << "   Experience Points: " << experience_points << endl;
            break;
        case MOVING_TO_GYM:
            cout << "heading to Pokemon Gym " << current_gym->GetId() << " at a speed of " << speed << " at each step of " << delta << "." << endl;
            cout << "   Stamina: " << stamina << endl;
            cout << "   Pokemon Dollars: " << pokemon_dollars << endl;
            cout << "   Experience Points: " << experience_points << endl;
            break;
        case IN_CENTER:
            cout << "inside Pokemon Center " << current_center->GetId() << endl;
            cout << "   Stamina: " << stamina << endl;
            cout << "   Pokemon Dollars: " << pokemon_dollars << endl;
            cout << "   Experience Points: " << experience_points << endl;
            break;
        case IN_GYM:
            cout << "inside Pokemon Gym " << current_gym->GetId() << endl;
            cout << "   Stamina: " << stamina << endl;
            cout << "   Pokemon Dollars: " << pokemon_dollars << endl;
            cout << "   Experience Points: " << experience_points << endl;
            break;
        case TRAINING_IN_GYM:
            cout << "training in Pokemon Gym " << current_gym->GetId() << endl;
            cout << "   Stamina: " << stamina << endl;
            cout << "   Pokemon Dollars: " << pokemon_dollars << endl;
            cout << "   Experience Points: " << experience_points << endl;
            break;
        case RECOVERING_STAMINA:
            cout << "recovering stamina in Pokemon Center " << current_center->GetId() << endl;
            cout << "   Stamina: " << stamina << endl;
            cout << "   Pokemon Dollars: " << pokemon_dollars << endl;
            cout << "   Experience Points: " << experience_points << endl;
            break;
        case EXHAUSTED:
            cout << "\n   Stamina: " << stamina << endl;
            cout << "   Pokemon Dollars: " << pokemon_dollars << endl;
            cout << "   Experience Points: " << experience_points << endl;
            break;
    }
}
bool Pokemon::Update()
{
    switch (state) {
        case STOPPED:
            return false;
        case MOVING:
            if (is_in_center) {
                current_center->RemoveOnePokemon();
                is_in_center = false;
            }
            if (is_in_gym) {
                current_gym->RemoveOnePokemon();
            is_in_gym = false;
            }
            bool HasArrived;
            HasArrived = UpdateLocation();
            if (HasArrived)
            {
                state = STOPPED;
                is_in_gym = false;
                is_in_center = false;
                return true;
            }
            else {
                return false;
            }
        case MOVING_TO_CENTER:
            if (is_in_center) {
                current_center->RemoveOnePokemon();
                is_in_center = false;
            }
            if (is_in_gym) {
                current_gym->RemoveOnePokemon();
                is_in_gym = false;
            }
            bool HasArrivedAtCenter;
            HasArrivedAtCenter = UpdateLocation();
            if (HasArrivedAtCenter)
            {
            state = IN_CENTER;
            current_center->AddOnePokemon();
            is_in_center = true;
            return true;
            } else {
            return false;
            }
        case MOVING_TO_GYM:
            if (is_in_center) {
                current_center->RemoveOnePokemon();
                is_in_center = false;
            }
            if (is_in_gym) {
                current_gym->RemoveOnePokemon();
                is_in_gym = false;
            }
            bool HasArrivedAtGym;
            HasArrivedAtGym = UpdateLocation();
            if (HasArrivedAtGym)
            {
            state = IN_GYM;
            current_gym->AddOnePokemon();
            is_in_gym = true;
            return true;
            } else {
            return false;
        }
        case IN_CENTER:
            return false;
        case IN_GYM:
            return false;
        case TRAINING_IN_GYM:
            if (current_gym->IsAbleToTrain(training_units_to_buy, pokemon_dollars, stamina))
            {
                stamina = stamina - current_gym->GetStaminaCost(training_units_to_buy);
                pokemon_dollars = pokemon_dollars - current_gym->GetDollarCost(training_units_to_buy);
                experience_points = experience_points + current_gym->TrainPokemon(training_units_to_buy);
                if (training_units_to_buy == 1)
                    cout << "** " << name << " completed 1 training unit!" << endl;
                else
                    cout << "** " << name << " completed " << training_units_to_buy << " training units!" << endl;
                if (experience_points == 1)
                    cout << "** " << name << " gained 1 experience point!" << endl;
                else
                    cout << "** " << name << " gained " << experience_points << " experience points!" << endl;
            } else
                cout << "Unable to train" << endl;
            state = IN_GYM;
            return true;
        case RECOVERING_STAMINA:
            if (current_center->CanAffordStaminaPoints(stamina_points_to_buy, pokemon_dollars)) {
                stamina = stamina + current_center->DistributeStamina(stamina_points_to_buy);
                pokemon_dollars = pokemon_dollars - current_center->GetDollarCost(stamina_points_to_buy);
                if (stamina_points_to_buy == 1)
                    cout << "** " << name << " recovered 1 stamina point!" << endl;
                else
                    cout << "** " << name << " recovered " << stamina_points_to_buy << " stamina points!" << endl;
            }
            else
                cout << "Not enough Pokemon dollars to recover stamina." << endl;
            state = IN_CENTER;
            return true;
    }
}
bool Pokemon::UpdateLocation()
{
    Vector2D DestMinusLoc = destination - location;
    if (fabs(DestMinusLoc.x) <= fabs(delta.x) && fabs(DestMinusLoc.y) <= fabs(delta.y)) //within one step of destination
    {
        if (!IsExhausted()) {
            location = destination;
            cout << "You've arrived." << endl;
            state = STOPPED;
            pokemon_dollars = pokemon_dollars + GetRandomAmountOfPokemonDollars();
            stamina = stamina - 1;
            return true;
        } else {
            location = destination;
            cout << "You've arrived." << endl;
            state = EXHAUSTED;
            cout << name << " is exhausted" << endl;
            pokemon_dollars = pokemon_dollars + GetRandomAmountOfPokemonDollars();

        }
    }
    else {
        if (!IsExhausted()) {
            location = location + delta;
            cout << "You've moved" << endl;
            pokemon_dollars = pokemon_dollars + GetRandomAmountOfPokemonDollars();
            stamina = stamina - 1;
            return false;
        } else {
            cout << name << " is exhausted" << endl;
            state = EXHAUSTED;
            return false;
        }
    }
}
void Pokemon::SetupDestination(Point2D dest)
{
    destination = dest;
    delta = (destination - location) * (speed / GetDistanceBetween(destination, location));
}


double GetRandomAmountOfPokemonDollars()
{
    double amount;

    amount = rand() % 300;
    amount = amount / 100;

    return amount;
}

Pokemon::~Pokemon()
{
    cout << "Pokemon destructed" << endl;
}

string Pokemon::GetName()
{
    return name;
}