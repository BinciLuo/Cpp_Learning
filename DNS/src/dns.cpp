#include <fstream>
#include <map>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "dns.hpp"

DNS_Server::DNS_Server(std::string dns_config_fp, int port, std::string remote_addr) {
    // 加载DNS配置文件
    loadDNSConfig(dns_config_fp);
    // 创建Socket
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);  // DNS默认端口
    // 绑定Socket
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
}

DNS_Server::~DNS_Server() {
    // 关闭Socket
    close(serverSocket);
}

void DNS_Server::loadDNSConfig(const std::string& configFile) {
    std::ifstream file(configFile);
    std::string domain, ipAddress;
    printf("[INIT] Loading DNS config: %s\n", configFile.c_str());
    while (file >> domain >> ipAddress) {
        dnsConfig[domain] = ipAddress;
        printf("    %s:%s\n", domain.c_str(), ipAddress.c_str());
    }
    printf("    Finish load DNS config: %s\n", configFile.c_str());
    fflush(stdout);
}

std::string DNS_Server::resolveDNS(const std::string& domain) {
    auto it = dnsConfig.find(domain);
    return (it != dnsConfig.end()) ? it->second : "Not Found";
}

void DNS_Server::startListening() {
    while (true) {
        char buffer[1024];
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLen = sizeof(clientAddress);
        // 接收DNS请求
        recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddress, &clientAddressLen);
        // 解析DNS请求的域名
        std::string requestedDomain(buffer);
        // 调用resolveDNS函数解析域名
        std::string ipAddress = resolveDNS(requestedDomain);
        // 构造DNS响应
        std::string dnsResponse = "DNS Response: " + ipAddress;
        // 发送DNS响应
        sendto(serverSocket, dnsResponse.c_str(), dnsResponse.size(), 0, (struct sockaddr*)&clientAddress, clientAddressLen);
    }
}