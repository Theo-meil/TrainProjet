//Pour le système de contrôle central, coordonnant les trains et les stations.
#ifndef CONTROL_H
#define CONTROL_H

#include "Train.h"
#include "Station.h"
#include <vector>

class Control {
public:
    Control();
    void addTrain(Train* train);
    void addStation(Station* station);
    void updateSystem();
    void startNextTrain();

private:
    std::vector<Train*> trains;
    std::vector<Station*> stations;
    Station* findStationForTrain(Train* train);
    void updateTrains();
    void updateStations();
    void manageTrainArrivals();
    void manageTrainDepartures();
};

#endif // CONTROL_H
