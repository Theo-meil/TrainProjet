//Pour la gestion de la communication entre les trains, les stations, et le syst�me de contr�le.
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <string>

class Communication {
public:
    Communication();
    void sendMessage(const std::string& message);
    std::string receiveMessage();
    // Autres m�thodes de communication

private:
    // Attributs pour g�rer la communication, comme des sockets ou des files d'attente
};

#endif // COMMUNICATION_H
