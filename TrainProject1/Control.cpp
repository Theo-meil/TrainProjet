//Pour le système de contrôle central, coordonnant les trains et les stations.
#include "Control.h"
#include "Station.h"
#include "Train.h"
#include <algorithm> // Ajout pour utiliser std::min_element

Control::Control() {
    std::vector<int> positionsDesStations = { 0, 1000, 2000, 3000, 4000, 5000 };
    for (int pos : positionsDesStations) {
        Station* station = new Station(pos);
        addStation(station);
    }
}


void Control::addTrain(Train* train) {
    trains.push_back(train);
}

void Control::addStation(Station* station) {
    stations.push_back(station);
}

void Control::updateSystem() {
    updateTrains();
    updateStations();
    manageTrainArrivals();
    manageTrainDepartures();
    startNextTrain();
    std::cout << "Mise a jour du systeme de controle." << std::endl;

}

void Control::updateTrains() {
    for (auto& train : trains) {
        train->update(); // Met à jour la position du train, par exemple

        // Vérifiez l'état du train pour savoir s'il est arrivé à une station
        if (train->getEtat() == EtatTrain::EN_STATION) {
            Station* currentStation = findStationForTrain(train); // Trouver la station correspondante
            int passengersToEmbark = train->getPassengersToEmbark();
            int passengersToDisembark = currentStation->getPassengersWaiting();

            currentStation->embarquerPassagers(passengersToEmbark);
            currentStation->debarquerPassagers(passengersToDisembark);
        }
    }
}

void Control::updateStations() {
    for (auto& station : stations) {
        // Vous pouvez ajouter ici des logiques pour mettre à jour l'état des stations
        station->update(); // Cette fonction doit être définie dans Station.cpp
    }
}

void Control::manageTrainArrivals() {
    for (auto& train : trains) {
        if (train->getEtat() == EtatTrain::EN_STATION) {
            Station* currentStation = findStationForTrain(train); // Trouver la station correspondante
            int passengersToEmbark = train->getPassengersToEmbark();
            int passengersToDisembark = currentStation->getPassengersWaiting();

            currentStation->embarquerPassagers(passengersToEmbark);
            currentStation->debarquerPassagers(passengersToDisembark);
        }
    }
}

void Control::manageTrainDepartures() {
    for (auto& train : trains) {
        if (train->isReadyToDepart()) {  // Supposons que isReadyToDepart est une méthode dans Train
            train->stop();
            Station* currentStation = findStationForTrain(train);
            currentStation->departTrain(train->getId());
            startNextTrain();  // Démarrer le prochain train après le départ de celui-ci
        }
    }
}


Station* Control::findStationForTrain(Train* train) {
    Station* closestStation = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    for (Station* station : stations) {
        float distance = std::abs(station->getPosition() - train->getPosition());
        if (distance < minDistance) {
            minDistance = distance;
            closestStation = station;
        }
    }

    return closestStation;
}


void Control::startNextTrain() {
    for (auto& train : trains) {
        if (train->canStart()) {  // Supposons que canStart est une méthode dans Train
            train->start();
            break;
        }
    }
}
