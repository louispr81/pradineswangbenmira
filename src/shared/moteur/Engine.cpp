#include "Engine.h"
#include <iostream>
#include <mutex>

using namespace state;
using namespace std;
namespace moteur{

Engine::Engine () {
    cout<<"Engine launched"<<endl;
}

Engine::Engine (state::State* currentState) {
    this->currentState=currentState;
    std::vector<Command*> listeCommandes;
    CommandMove *move = new CommandMove(currentState);
    CommandAttack *attack = new CommandAttack(currentState);
    CommandAttendre *attendre = new CommandAttendre(currentState);
    this->listeCommandes.push_back(move);
    this->listeCommandes.push_back(attack);
    this->listeCommandes.push_back(attendre);
}

state::State* Engine::getState() {
    return this->currentState;
}

void Engine::setState(state::State* state) {
    this->currentState=state;
}

Command* Engine::getCommands(){
   
    return currentCommands;
}

int Engine::update(CommandId cmd, MoveId move){
    if(cmd == ATTENDRE){
        this->currentCommands=this->listeCommandes[2];
        ((CommandAttendre*)this->currentCommands)->execute();
        return 2;
    }
    if(cmd == ATTACK){
        this->currentCommands=this->listeCommandes[1];
        std::vector<int> position;
        std::vector<int> positionEnemy;
        state::Joueur* joueurEnemy;
        position = currentState->getPersonnageActif()->getCell()->getCoordonees();
        joueurEnemy = currentState->getJoueurs()[((currentState->getJoueur()->getId()-40)+1)%2];     
        switch(move){
            case LEFT:
                position[0]=position[0]-1;
                if(0<position[0]-1<= currentState->getPlateau()->getSize()){
                    for(int i=0;i<joueurEnemy->getPersonnages().size();i++){
                        if(joueurEnemy->getPersonnages()[i]->getAlive()==true){
                            positionEnemy = joueurEnemy->getPersonnages()[i]->getCell()->getCoordonees();
                            if(position == positionEnemy){
                                ((CommandAttack*)this->currentCommands)->execute(joueurEnemy->getPersonnages()[i]);
                                return 1;
                            }
                        }
                    }
                    cout<<"There isn't any enemy here."<<endl;
                }
                else{
                    cout<<"You can't attack here."<<endl;
                }
                break;
            case RIGHT:
                position[0]=position[0]+1;
                if(0<position[0]+1<= currentState->getPlateau()->getSize()){
                    for(int i=0;i<joueurEnemy->getPersonnages().size();i++){
                        if(joueurEnemy->getPersonnages()[i]->getAlive()==true){
                            positionEnemy = joueurEnemy->getPersonnages()[i]->getCell()->getCoordonees();
                            if(position == positionEnemy){
                                ((CommandAttack*)this->currentCommands)->execute(joueurEnemy->getPersonnages()[i]);
                                return 1;
                            }
                        }
                    }
                    cout<<"There isn't any enemy here."<<endl;
                }
                else{
                    cout<<"You can't attack here."<<endl;
                }
            break;

            case UP:
                position[1]=position[1]-1;
                if(0<position[1]-1<= currentState->getPlateau()->getSize()){
                    for(int i=0;i<joueurEnemy->getPersonnages().size();i++){
                        if(joueurEnemy->getPersonnages()[i]->getAlive()==true){
                            positionEnemy = joueurEnemy->getPersonnages()[i]->getCell()->getCoordonees();
                            if(position == positionEnemy){
                                ((CommandAttack*)this->currentCommands)->execute(joueurEnemy->getPersonnages()[i]);
                                return 1;
                            }
                        }
                    }
                    cout<<"There isn't any enemy here."<<endl;
                }
                else{
                    cout<<"You can't attack here."<<endl;
                }
            break;

            case DOWN:
                position[1]=position[1]+1;
                if(0<position[1]+1<= currentState->getPlateau()->getSize()){
                    for(int i=0;i<joueurEnemy->getPersonnages().size();i++){
                        if(joueurEnemy->getPersonnages()[i]->getAlive()==true){
                            positionEnemy = joueurEnemy->getPersonnages()[i]->getCell()->getCoordonees();
                            if(position == positionEnemy){
                                ((CommandAttack*)this->currentCommands)->execute(joueurEnemy->getPersonnages()[i]);
                                return 1;
                            }
                        }                        
                    }
                    cout<<"There isn't any enemy here."<<endl;
                }
                else{
                    cout<<"You can't attack here."<<endl;
                }
            break;
        }

        return -1;
    }
    if(cmd == MOVE){        
        this->currentCommands=this->listeCommandes[0];
        ((CommandMove*)(this->currentCommands))->execute(move);
        return 0;
    }
    else{
        return -1;
    }  
}
std::vector<Command*> Engine::getListCommand(){
    return listeCommandes;
}
Engine::Engine (state::State* currentState,std::mutex* mutex) {
    this->currentState=currentState;
    std::vector<Command*> listeCommandes;
    CommandMove *move = new CommandMove(currentState);
    CommandAttack *attack = new CommandAttack(currentState);
    CommandAttendre *attendre = new CommandAttendre(currentState);
    std::vector<std::vector<int>> listeCommandToExecute;
    this->listeCommandes.push_back(move);
    this->listeCommandes.push_back(attack);
    this->listeCommandes.push_back(attendre);
    this->listeCommandToExecute=listeCommandToExecute;
    this->mutex=mutex;
}
void Engine::updateListCommandToExecute(CommandId cmd, MoveId move){
    std::vector<int> listCmdMove;
    listCmdMove.push_back((int)cmd);
    listCmdMove.push_back((int)move);
    mutex->lock();
    this->listeCommandToExecute.push_back(listCmdMove);
    mutex->unlock();
}

void Engine::runEngineThread(){
    while(1){
        if(this->listeCommandToExecute.size()>0){
            std::vector<int> cmd= this->listeCommandToExecute[0];
            Engine::update((CommandId)cmd[0],(MoveId)cmd[1]);
            mutex->lock();
            this->listeCommandToExecute.erase(listeCommandToExecute.begin());
            mutex->unlock();
        }
    }
}


Engine::~Engine(){

}
}