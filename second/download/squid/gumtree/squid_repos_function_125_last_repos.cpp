static int
client_comm_connect(int sock, const Ip::Address &addr)
{
    static struct addrinfo *AI = NULL;
    addr.getAddrInfo(AI);
    int res = connect(sock, AI->ai_addr, AI->ai_addrlen);
    Ip::Address::FreeAddr(AI);
    Ping::TimerStart();
    return res;
}