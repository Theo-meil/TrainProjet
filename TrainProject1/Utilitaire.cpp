//Contenant des fonctions utilitaires, comme des fonctions de calcul ou de log.
#include "Utilitaire.h"
#include <cmath>
#include <string>

namespace Utilitaire {

    float calculerDistance(float x1, float y1, float x2, float y2) {
        // Calculer la distance euclidienne entre deux points
        return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    }

    // Ajoutez ici d'autres fonctions utilitaires sp�cifiques � votre projet
    // Par exemple, des fonctions pour convertir des unit�s, calculer des vitesses, etc.

}
