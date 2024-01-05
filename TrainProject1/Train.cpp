//Pour gérer les caractéristiques et le comportement des rames de métro.
#include "Train.h"
#include "Control.h"
#include "Station.h"


Train::Train(int id, Control* control, Station* currentStation)
    : id(id), control(control), speed(VITESSE_CONSTANTE), position(0),
    etat(EtatTrain::ARRETE), comm(), nombrePassagers(0), capaciteMax(CAPACITE_MAX),
    direction(true), currentStation(currentStation), prochaineStationPosition(1000) {
    // Initialisation
}

void Train::start() {
    if (etat != EtatTrain::ARRETE) {
        std::cerr << "Le train doit être à l'arrêt pour démarrer." << std::endl;
        return;
    }
    std::cout << "Train " << id << " démarré." << std::endl;
    etat = EtatTrain::EN_MARCHE;
}

void Train::stop() {
    if (etat != EtatTrain::EN_MARCHE) {
        std::cerr << "Le train doit être en marche pour s'arrêter." << std::endl;
        return;
    }
    std::cout << "Train " << id << " arrêté." << std::endl;
    etat = EtatTrain::ARRETE;
}


void Train::update() {
    if (etat == EtatTrain::EN_STATION && waitingInStation) {
        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastStopTime).count() >= TEMPS_ATTENTE_STATION) {
            etat = EtatTrain::EN_MARCHE;
            waitingInStation = false;
            control->startNextTrain();

            if (position == DERNIERE_STATION_POSITION) {
                direction = !direction;
                // Réinitialiser la position de la prochaine station pour le trajet retour
                prochaineStationPosition -= 1000;
            }
            else {
                // Mise à jour de la position de la prochaine station pour le trajet normal
                prochaineStationPosition += 1000; // Si les stations sont espacées de 1000 unités
            }
        }
    }

    if (etat == EtatTrain::EN_MARCHE) {
        position += direction ? VITESSE_CONSTANTE : -VITESSE_CONSTANTE;

        // Vérification pour l'arrêt à la prochaine station
        if (position == prochaineStationPosition) {
            etat = EtatTrain::EN_STATION;
            lastStopTime = std::chrono::steady_clock::now();
            waitingInStation = true;
            embarquerPassagers();
            debarquerPassagers();
        }
    }

    std::cout << "Mise a jour du train " << id << ": Etat = " << static_cast<int>(etat) << ", Position = " << position << std::endl;
}


void Train::communicate(const std::string& message) {
    comm.sendMessage(message);
}

float Train::getPosition() const {
    return position;
}

EtatTrain Train::getEtat() const {
    return etat;
}

void Train::embarquerPassagers() {
    int nombreAleatoire = genererNombreAleatoire(0, CAPACITE_MAX - nombrePassagers);
    nombrePassagers += nombreAleatoire;
    std::cout << nombreAleatoire << " passagers embarqués." << std::endl;
}

void Train::debarquerPassagers() {
    int nombreAleatoire = genererNombreAleatoire(0, nombrePassagers);
    nombrePassagers -= nombreAleatoire;
    std::cout << nombreAleatoire << " passagers débarqués." << std::endl;
}

void Train::afficherNombrePassagers() const {
    std::cout << "Nombre de passagers dans le train " << id << ": " << nombrePassagers << std::endl;
}

int Train::genererNombreAleatoire(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}



int Train::getId() const {
    return id; // Supposant que 'id' est une variable membre de Train
}


int Train::getPassengersToDisembark() const {
    // Ajoutez ici la logique pour obtenir le nombre de passagers qui doivent débarquer du train
    return 0; // Remplacez par la logique appropriée
}

int Train::getPassengersToEmbark() const {
    if (currentStation) {
        int waitingPassengers = currentStation->getPassengersWaiting();
        int availableSpace = capaciteMax - nombrePassagers;
        return std::min(waitingPassengers, availableSpace);
    }
    return 0;
}

bool Train::isReadyToDepart() const {
    // Exemple de logique : le train est prêt à partir si 
    // il est en station (EN_STATION) et a attendu un certain temps
    if (etat == EtatTrain::EN_STATION) {
        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastStopTime).count() >= TEMPS_ATTENTE_STATION) {
            return true;
        }
    }
    return false;
}

bool Train::canStart() const {
    // Exemple de condition : le train peut démarrer s'il est actuellement arrêté et a terminé le chargement des passagers
    if (etat == EtatTrain::ARRETE) {
        // Vérifiez si d'autres conditions sont remplies, par exemple, le temps passé en station
        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastStopTime).count() >= TEMPS_MINIMUM_STATION) {
            return true;
        }
    }
    return false;
}


