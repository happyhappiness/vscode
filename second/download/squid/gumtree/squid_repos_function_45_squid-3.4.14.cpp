static int
client_comm_bind(int sock, const Ip::Address &addr)
{
    /* Set up the source socket address from which to send. */
    static struct addrinfo *AI = NULL;
    addr.getAddrInfo(AI);
    int res = bind(sock, AI->ai_addr, AI->ai_addrlen);
    Ip::Address::FreeAddrInfo(AI);
    return res;
}