void
Ip::Address::InitAddr(struct addrinfo *&ai)
{
    if (ai == NULL) {
        ai = new addrinfo;
        memset(ai,0,sizeof(struct addrinfo));
    }

    // remove any existing data.
    if (ai->ai_addr) delete ai->ai_addr;

    ai->ai_addr = (struct sockaddr*)new sockaddr_in6;
    memset(ai->ai_addr, 0, sizeof(struct sockaddr_in6));

    ai->ai_addrlen = sizeof(struct sockaddr_in6);

}