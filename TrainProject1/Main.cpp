#include "Control.h"
#include "Train.h"
#include "Station.h"

int main() {
    Control controlSystem;

    // Création et ajout des trains
    Train* train1 = new Train(1, &controlSystem, nullptr); // nullptr pour currentStation si non défini
    Train* train2 = new Train(2, &controlSystem, nullptr);
    controlSystem.addTrain(train1);
    controlSystem.addTrain(train2);

    // La création des stations est déjà gérée dans le constructeur de Control

    // Simulation d'un certain nombre de cycles de mise à jour
    for (int i = 0; i < 10; ++i) {
        controlSystem.updateSystem();
        // Ajoutez une pause si nécessaire, par exemple std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Nettoyage de la mémoire
    delete train1;
    delete train2;

    // Ajoutez du code pour nettoyer les stations si elles sont créées dynamiquement

    return 0;
}
