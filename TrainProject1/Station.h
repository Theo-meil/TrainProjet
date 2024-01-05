//Pour gérer les stations, y compris l'embarquement et le débarquement des passagers.
#ifndef STATION_H
#define STATION_H

#include <vector>
#include <iostream>
#include <random>

class Station {
public:
    static const int MAX_PASSAGERS = 100;// Capacité maximale de la station
    Station(int id);
    void arriveTrain(int trainId);
    void departTrain(int trainId);
    void embarquerPassagers(int nombre);
    void debarquerPassagers(int nombre);
    void afficherNombrePassagersQuai() const;  // Nouvelle méthode
    void update();
    float position;
    float getPosition() const;
    static int genererNombreAleatoire(int min, int max);
    int getPassengersWaiting() const;

private:
    int id;
    std::vector<int> trainsInStation;
    int nombrePassagers; // Nombre de passagers sur le quai
};


#endif // STATION_H
