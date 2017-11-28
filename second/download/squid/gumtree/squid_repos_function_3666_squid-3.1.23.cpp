void IpAddress::FreeAddrInfo(struct addrinfo *&ai) const
{
    if (ai == NULL) return;

    if (ai->ai_addr) delete ai->ai_addr;

    ai->ai_addr = NULL;

    ai->ai_addrlen = 0;

    // NP: name fields are NOT allocated at present.
    delete ai;

    ai = NULL;
}