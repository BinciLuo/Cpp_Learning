#ifndef DNS_H
#define DNS_H

#include <string>
#include <map>

class DNS_Server {
private:
    std::map<std::string, std::string> dnsConfig;
    int serverSocket;

public:
    DNS_Server(std::string dns_config_fp, int port, std::string remote_addr);
    ~DNS_Server();

    void loadDNSConfig(const std::string& configFile);
    std::string resolveDNS(const std::string& domain);
    void startListening();
};

#endif // DNS_H
