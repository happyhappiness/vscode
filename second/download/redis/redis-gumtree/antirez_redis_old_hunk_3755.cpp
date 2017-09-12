    int s;
    struct sockaddr_un sa;

    if ((s = socket(AF_LOCAL,SOCK_STREAM,0)) == -1) {
        anetSetError(err, "socket: %s\n", strerror(errno));
        return ANET_ERR;
    }
    memset(&sa,0,sizeof(sa));
    sa.sun_family = AF_LOCAL;
    strncpy(sa.sun_path,path,sizeof(sa.sun_path)-1);
    if (bind(s,(struct sockaddr*)&sa,SUN_LEN(&sa)) == -1) {
        anetSetError(err, "bind: %s\n", strerror(errno));
        close(s);
        return ANET_ERR;
    }
    if (listen(s, 511) == -1) { /* the magic 511 constant is from nginx */
        anetSetError(err, "listen: %s\n", strerror(errno));
        close(s);
        return ANET_ERR;
    }
    return s;
}

