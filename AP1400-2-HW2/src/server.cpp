#include"server.h"
#include"client.h"
#include"crypto.h"
#include<random>
#include<iostream>
#include<regex>
using std::map;
using std::shared_ptr;
std::vector<std::string> pending_trxs = {};

void show_wallets(const  Server& server){
    std::cout << std::string(20, '*') << std::endl;
    for(const auto& client: server.clients)
        std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}
Server::Server(){
    clients = map<shared_ptr<Client>, double>{};
}
shared_ptr<Client> Server::add_client(std::string id){
    if (get_client(id) != nullptr){
        // std::default_random_engine e;
        // std::uniform_int_distribution<int>dis(1000, 9999);
        // int randNum = dis(e);
        // id += std::to_string(randNum);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(1000, 9999);
        int randNum = dis(gen);
        id += std::to_string(randNum);
    }
    shared_ptr<Client> added = std::make_shared<Client>(id, *this);
    clients.insert(std::make_pair(added, 5));
    return added;
}
shared_ptr<Client> Server::get_client(const std::string id) const{
    for (auto rollPair : clients){
        if ((rollPair.first)->get_id() == id)
            return rollPair.first;
    }
    return nullptr;
}
double Server::get_wallet(std::string id)const{
    for (auto rollPair : clients){
        if ((rollPair.first)->get_id() == id)
            return rollPair.second;
    }
    return 0;   
}
bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value){
    std::regex pattern("([a-zA-Z]+)-([a-zA-Z]+)-([\\d.]+)");
    std::smatch matches;
    if (!std::regex_match(trx, matches, pattern)){
        throw std::runtime_error("input trx in not valid!");
        return false;
    }
        
    sender = matches[1];
    receiver = matches[2];
    value = std::stod(matches[3]);
    return true;
}
bool Server::add_pending_trx(std::string trx, std::string signature) const{
    std::string sender, receiver;
    double value;
    try{
        parse_trx(trx, sender, receiver, value);
    } catch (std::runtime_error e){
        std::cout << e.what() << std::endl;
        return false;
    }
    shared_ptr<Client>senderPtr = get_client(sender);
    if (senderPtr == nullptr)
        return false;
    if (crypto::verifySignature(senderPtr->get_publickey(), senderPtr->get_id(), signature) == false)
        return false;
    if (senderPtr->get_wallet() < value)
        return false;
    pending_trxs.push_back(trx);
    return true;
}