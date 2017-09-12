int anetResolve(char *err, char *host, char *ipbuf, size_t ipbuf_len)
{
    struct addrinfo hints, *info;
    void *addr;
    int rv;

    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_INET;

    if ((rv = getaddrinfo(host, NULL, &hints, &info)) != 0) {
        anetSetError(err, "%s", gai_strerror(rv));
        return ANET_ERR;
    }
    if (info->ai_family == AF_INET) {
        struct sockaddr_in *sa = (struct sockaddr_in *)info->ai_addr;
        addr = &(sa->sin_addr);
    }

    inet_ntop(info->ai_family, addr, ipbuf, ipbuf_len);
    freeaddrinfo(info);
    return ANET_OK;
}