#ifndef TRAIN_H
#define TRAIN_H

#include "Station.h"
#include "Communication.h"
#include <random>
#include <iostream>
#include<chrono>

enum class EtatTrain {
    EN_MARCHE,
    ARRETE,
    EN_STATION,
    EN_ATTENTE
};

class Control;

class Train {
public:
    static const int CAPACITE_MAX = 100;
    static const int VITESSE_CONSTANTE = 500;
    Train(int id, Control* control, Station* currentStation);
    void start();
    void stop();
    void update();
    void communicate(const std::string& message);
    void embarquerPassagers();
    void debarquerPassagers();
    void afficherNombrePassagers() const;  
    int getPassengersToEmbark() const;
    float getPosition() const;
    EtatTrain getEtat() const;
    static int genererNombreAleatoire(int min, int max);
    bool isReadyToDepart() const;
    int getId() const;
    static const int TEMPS_ATTENTE_STATION = 30;
    bool canStart() const;
    static const int TEMPS_MINIMUM_STATION = 30;
    static const int DERNIERE_STATION_POSITION = 5000; // Position de la dernière station

private:
    Control* control;
    int id;
    float speed;
    float position;
    Communication comm;
    EtatTrain etat;
    int nombrePassagers;
    int prochaineStationPosition;
    std::chrono::steady_clock::time_point lastStopTime;
    bool waitingInStation = false;
    const int capaciteMax = CAPACITE_MAX;
    int getPassengersToDisembark() const;
    Station* currentStation;
    bool direction;
};


#endif // TRAIN_H
