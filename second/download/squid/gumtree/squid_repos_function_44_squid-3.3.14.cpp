static int
client_comm_bind(int sock, const Ip::Address &addr)
{

    int res;

    static struct addrinfo *AI = NULL;

    /* Set up the source socket address from which to send. */

    addr.GetAddrInfo(AI);

    res = bind(sock, AI->ai_addr, AI->ai_addrlen);

    addr.FreeAddrInfo(AI);

    return res;
}