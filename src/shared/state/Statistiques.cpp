#include "Statistiques.h" 
#include <iostream>
using namespace state;


Statistiques::Statistiques (){}
Statistiques::~Statistiques (){}


void Statistiques::setVie (int vie){
    (*this).vie=vie;
}
void Statistiques::setVie_max (int vie_max){
    (*this).vie_max=vie_max;
}
void Statistiques::setPoint_mouvement (int point_mouvement){
    (*this).point_mouvement=point_mouvement;
}
void Statistiques::setPoint_mouvement_max (int point_mouvement_max){
    (*this).point_mouvement_max=point_mouvement_max;
}
void Statistiques::setForce (int force){
    (*this).force=force;
}
void Statistiques::setIntelligence (int intelligence){
    (*this).intelligence=intelligence;
}
void Statistiques::setVitesse (int vitesse){
    (*this).vitesse=vitesse;
}
void Statistiques::setDefense (int defense){
    (*this).defense=defense;
}
void Statistiques::setResistance (int resistance){
    (*this).resistance=resistance;
}
void Statistiques::setTechnique (int technique){
    (*this).technique=technique;
}
void Statistiques::setExperience (int experience){
    (*this).experience=experience;
}
void Statistiques::setExperience_max (int experience_max){
    (*this).experience_max=experience_max;
}
void Statistiques::setNiveau (int niveau){
    (*this).niveau=niveau;
}
int Statistiques::getVie (){
    return (*this).vie;
}

int Statistiques::getVie_max (){
    return (*this).vie_max;
}
int Statistiques::getPoint_mouvement (){
    return (*this).point_mouvement;
}
int Statistiques::getPoint_mouvement_max (){
    return (*this).point_mouvement_max;
}
int Statistiques::getForce (){
    return (*this).force;
}
int Statistiques::getIntelligence (){
    return (*this).intelligence;
}
int Statistiques::getVitesse (){
    return (*this).vitesse;
}
int Statistiques::getDefense (){
    return (*this).defense;
}
int Statistiques::getResistance (){
    return (*this).resistance;
}
int Statistiques::getTechnique (){
    return (*this).technique;
}
int Statistiques::getExperience (){
    return (*this).experience;
}
int Statistiques::getExperience_max (){
    return (*this).experience_max;
}
int Statistiques::getNiveau (){
    return (*this).niveau;
}
void Statistiques::print(){
    std::cout<<"---------------STATISTIQUES---------------"<<std::endl;
    std::cout<<"niveau="<<this->niveau<<std::endl;
    std::cout<<"XP="<<this->experience<<"/"<<this->experience_max<<std::endl;
    std::cout<<"HP="<<this->vie<<"/"<<this->vie_max<<std::endl;
    std::cout<<"PM="<<this->point_mouvement<<"/"<<this->point_mouvement_max<<std::endl;
    std::cout<<"force="<<this->force<<std::endl;
    std::cout<<"intelligence="<<this->intelligence<<std::endl;
    std::cout<<"vitesse="<<this->vitesse<<std::endl;
    std::cout<<"defense="<<this->defense<<std::endl;
    std::cout<<"resistance="<<this->resistance<<std::endl;
    std::cout<<"technique="<<this->technique<<std::endl;
    std::cout<<"----------------------------------------"<<std::endl;
}
