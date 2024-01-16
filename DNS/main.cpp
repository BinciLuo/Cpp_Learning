#include <iostream>
#include <fstream>
#include <map>
#include <nlohmann/json.hpp>
#include "src/dns.hpp"
#include "src/utils.hpp"

using json = nlohmann::json;


int main(int argc, char* argv[]) {
    auto configJson = readJsonFile("config.json");
    auto dns_config = configJson["dns_config"].template get<std::string>();
    auto dns_port = configJson["dns_port"].template get<int>();
    auto remote_dns_addr = configJson["remote_dns_addr"].template get<std::string>();

    DNS_Server dnsServer(dns_config, dns_port, remote_dns_addr);
    dnsServer.startListening();

    return 0;
}
