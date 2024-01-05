//Pour g�rer les caract�ristiques et le comportement des rames de m�tro.
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
        std::cerr << "Le train doit �tre � l'arr�t pour d�marrer." << std::endl;
        return;
    }
    std::cout << "Train " << id << " d�marr�." << std::endl;
    etat = EtatTrain::EN_MARCHE;
}

void Train::stop() {
    if (etat != EtatTrain::EN_MARCHE) {
        std::cerr << "Le train doit �tre en marche pour s'arr�ter." << std::endl;
        return;
    }
    std::cout << "Train " << id << " arr�t�." << std::endl;
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
                // R�initialiser la position de la prochaine station pour le trajet retour
                prochaineStationPosition -= 1000;
            }
            else {
                // Mise � jour de la position de la prochaine station pour le trajet normal
                prochaineStationPosition += 1000; // Si les stations sont espac�es de 1000 unit�s
            }
        }
    }

    if (etat == EtatTrain::EN_MARCHE) {
        position += direction ? VITESSE_CONSTANTE : -VITESSE_CONSTANTE;

        // V�rification pour l'arr�t � la prochaine station
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
    std::cout << nombreAleatoire << " passagers embarqu�s." << std::endl;
}

void Train::debarquerPassagers() {
    int nombreAleatoire = genererNombreAleatoire(0, nombrePassagers);
    nombrePassagers -= nombreAleatoire;
    std::cout << nombreAleatoire << " passagers d�barqu�s." << std::endl;
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
    // Ajoutez ici la logique pour obtenir le nombre de passagers qui doivent d�barquer du train
    return 0; // Remplacez par la logique appropri�e
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
    // Exemple de logique : le train est pr�t � partir si 
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
    // Exemple de condition : le train peut d�marrer s'il est actuellement arr�t� et a termin� le chargement des passagers
    if (etat == EtatTrain::ARRETE) {
        // V�rifiez si d'autres conditions sont remplies, par exemple, le temps pass� en station
        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastStopTime).count() >= TEMPS_MINIMUM_STATION) {
            return true;
        }
    }
    return false;
}


