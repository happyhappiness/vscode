        close(s);
        return ANET_ERR;
    }
    return ANET_OK;
}

int anetTcpServer(char *err, int port, char *bindaddr)
{
    int s;
    struct sockaddr_in sa;

    if ((s = anetCreateSocket(err,AF_INET)) == ANET_ERR)
        return ANET_ERR;

    memset(&sa,0,sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bindaddr && inet_aton(bindaddr, &sa.sin_addr) == 0) {
        anetSetError(err, "invalid bind address");
        close(s);
        return ANET_ERR;
    }
    if (anetListen(err,s,(struct sockaddr*)&sa,sizeof(sa)) == ANET_ERR)
        return ANET_ERR;
    return s;
}

int anetUnixServer(char *err, char *path, mode_t perm)
{
    int s;
    struct sockaddr_un sa;

    if ((s = anetCreateSocket(err,AF_LOCAL)) == ANET_ERR)
