static int
client_comm_connect(int sock, const IpAddress &addr, struct timeval *tvp)
{
    int res;
    static struct addrinfo *AI = NULL;

    /* Set up the destination socket address for message to send to. */

    addr.GetAddrInfo(AI);

    res = connect(sock, AI->ai_addr, AI->ai_addrlen);

    addr.FreeAddrInfo(AI);

    if (tvp)
        (void) Now(tvp);

    return res;
}