static int
client_comm_connect(int sock, const Ip::Address &addr, struct timeval *tvp)
{
    /* Set up the destination socket address for message to send to. */
    static struct addrinfo *AI = NULL;
    addr.getAddrInfo(AI);
    int res = connect(sock, AI->ai_addr, AI->ai_addrlen);
    Ip::Address::FreeAddrInfo(AI);
    if (tvp)
        (void) Now(tvp);
    return res;
}