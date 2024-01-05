//Pour gérer les stations, y compris l'embarquement et le débarquement des passagers.
#include "Station.h"
#include <iostream>
#include <string>


Station::Station(int id) : id(id), position(0.0f), nombrePassagers(genererNombreAleatoire(0, MAX_PASSAGERS)) {
    // Initialisation de la station
}

void Station::update() {
    // Exemple : Ajoutez des passagers de manière aléatoire
    nombrePassagers += genererNombreAleatoire(0, 5); // Ajoute un nombre aléatoire de passagers
    if (nombrePassagers > MAX_PASSAGERS) nombrePassagers = MAX_PASSAGERS;
}


void Station::arriveTrain(int trainId) {
    trainsInStation.push_back(trainId);
    std::cout << "Train " << trainId << " est arrivé en station " << id << std::endl;
}

void Station::departTrain(int trainId) {
    trainsInStation.erase(std::remove(trainsInStation.begin(), trainsInStation.end(), trainId), trainsInStation.end());
    std::cout << "Train " << trainId << " a quitté la station " << id << std::endl;
}


void Station::embarquerPassagers(int nombre) {
    if (nombre > nombrePassagers) nombre = nombrePassagers;
    nombrePassagers -= nombre;
    std::cout << "Station " << id << ": " << nombre << " passagers embarques." << std::endl;

}
void Station::debarquerPassagers(int nombre) {
    nombrePassagers += nombre;
    if (nombrePassagers > MAX_PASSAGERS) nombrePassagers = MAX_PASSAGERS;
}

void Station::afficherNombrePassagersQuai() const {
    std::cout << "Nombre de passagers sur le quai de la station " << id << ": " << nombrePassagers << std::endl;
}

int Station::getPassengersWaiting() const {
    return nombrePassagers; // Retourne le nombre actuel de passagers en attente
}

int Station::genererNombreAleatoire(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

float Station::getPosition() const {
    // Retournez la position de la station
    return position; // Assurez-vous qu'une variable 'position' est bien définie et initialisée
}