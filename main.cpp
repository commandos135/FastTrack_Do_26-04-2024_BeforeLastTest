#include <iostream>
#include <unordered_map>
#include <memory>

#define RRC_MSG_SIZE 100

struct RRCConnectionSetupRequest {
   int ueId;
     int accessType;
};

class Subscriber {
public:
    Subscriber(int ueId, int accessType) : ueId_(ueId), accessType_(accessType) {}
     int getUeId() const { return ueId_; }
   int getAccessType() const { return accessType_; }
private:
     int ueId_;
    int accessType_;
};
// // example of a SERVER/side requests

void sendRRCMessage(const char* message, int size) {
    std::cout << "Sending !RRC! message: " << message << std::endl;
}

bool receiveRRCMessage(char* buffer, int size) {
   std::cout << "Receiving RRC message..." << std::endl;
     memcpy(buffer, "Valid RRC message", size);
    return true;
}

class RRCServer {
public:
    void registerSubscriber(int ueId, int accessType) {
        subscribers_[ueId] = std::make_unique<Subscriber>(ueId, accessType);
    }

    void handleConnectionRequest() {
        char message[RRC_MSG_SIZE];
        if (!receiveRRCMessage(message, RRC_MSG_SIZE)) {
            std::cerr << "Error receiving RRC message." << std::endl;
            return;
        }

        RRCConnectionSetupRequest request;
    }

    // example of sending a connection request from a UE (CLIENT-side), so it'll be an interaction not only from a server side ;)
    bool sendConnectionRequest(int ueId, int accessType) {
        char message[RRC_MSG_SIZE];
        snprintf(message, RRC_MSG_SIZE, "Connection request from UE: %d, Access Type: %d", ueId, accessType);
        sendRRCMessage(message, RRC_MSG_SIZE);

        return receiveRRCMessage(message, RRC_MSG_SIZE);
    }

private:
    std::unordered_map<int, std::unique_ptr<Subscriber>> subscribers_;
};

int main() {
    RRCServer server;

    server.registerSubscriber(12345, 1);
    server.registerSubscriber(54321, 2);

    // example of a client/side requests
    if (server.sendConnectionRequest(12345, 1)) {
        std::cout << "UE 12345 connected successfully, YRA :D" << std::endl;
    }
    else {
        std::cerr << "failed to connect UE 12345 :(" << std::endl;
    }
    // we can add another connection request for UE 54321

    return 0;
}
