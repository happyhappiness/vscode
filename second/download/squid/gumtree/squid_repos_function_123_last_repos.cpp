static int
client_comm_bind(int sock, const Ip::Address &addr)
{
    static struct addrinfo *AI = NULL;
    addr.getAddrInfo(AI);
    int res = bind(sock, AI->ai_addr, AI->ai_addrlen);
    Ip::Address::FreeAddr(AI);
    return res;
}