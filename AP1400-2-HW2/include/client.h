#ifndef CLIENT_H
#define CLIENT_H
#include<string>
#include"server.h"

class Server;

class Client{
    public:
        Client(std::string id, const Server& server);
        std::string get_id() const;
        std::string get_publickey() const;
        double get_wallet() const;
        std::string sign(std::string txt)const;
        bool transfer_money(std::string receiver, double value);
        size_t generate_nonce();
    private:
        const Server* const server;
        const std::string id;
        std::string public_key;
        std::string private_key;
};

#endif