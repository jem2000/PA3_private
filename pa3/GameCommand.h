//
// Created by justi on 11/19/2019.
//

#ifndef PA3_GAMECOMMAND_H
#define PA3_GAMECOMMAND_H



#include "Model.h"

class GameCommand {
public:
    void DoMoveCommand(Model & model, int pokemon_id, Point2D p1);
    void DoMoveToCenterCommand(Model & model, int pokemon_id, int center_id);
    void DoMoveToGymCommand(Model & model, int pokemon_id, int gym_id);
    void DoStopCommand(Model & model, int pokemon_id);
    void DoTrainInGymCommand(Model & model, int pokemon_id, unsigned int training_units);
    void DoRecoverInCenterCommand(Model& model, int pokemon_id, unsigned int stamina_points);
    void DoGoCommand(Model& model, View& view);
    void DoRunCommand(Model& model, View& view);

};


#endif //PA3_GAMECOMMAND_H
