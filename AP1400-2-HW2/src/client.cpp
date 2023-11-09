#include"client.h"
#include"server.h"
#include"crypto.h"
#include<random>

using std::string;

Client::Client(string id, const Server& server):id(id), server(&server){
    crypto::generate_key(public_key, private_key);
}
string Client::get_id() const{
    return id;
}
string Client::get_publickey()const{
    return public_key;
}
double Client::get_wallet()const{
    return server->get_wallet(get_id());
}

std::string Client::sign(std::string txt) const{
    return crypto::signMessage(private_key, txt);
}
bool Client::transfer_money(std::string receiver, double value){
    if (server->get_client(receiver) == nullptr)
        return false;
    string trx;
    trx = id + "-" + receiver + "-" + std::to_string(value);
    if (server->add_pending_trx(trx, sign(id)) == false)
        return false;
    return true;
}
size_t Client::generate_nonce(){
    std::uniform_int_distribution<int>dis(10, 99);
    std::default_random_engine e;
    return dis(e);
}