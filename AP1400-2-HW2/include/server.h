#ifndef SERVER_H
#define SERVER_H

#include<string>
#include<memory>
#include<map>
#include<vector>
#include"client.h"

class Client;

class Server{
    public:
        Server();
        std::shared_ptr<Client> add_client(std::string id);
        std::shared_ptr<Client> get_client(const std::string id) const;
        double get_wallet(std::string id)const;
        //static修饰类的成员函数，表示不会修改或使用类实例中的成员
        static bool parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value);
        bool add_pending_trx(std::string trx, std::string signature)const;
        size_t mine();

    private:
        std::map<std::shared_ptr<Client>, double> clients;
    friend void show_wallets(const Server& server);
};
    extern std::vector<std::string> pending_trxs;

#endif