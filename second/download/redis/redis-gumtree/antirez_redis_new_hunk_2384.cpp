    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bindaddr_count) {
        for (j = 0; j < bindaddr_count; j++) {
            if (inet_aton(bindaddr[j], &sa.sin_addr) == 0) {
                anetSetError(err, "invalid bind address");
                close(s);
                return ANET_ERR;
            }
            if (anetListen(err,s,(struct sockaddr*)&sa,sizeof(sa)) == ANET_ERR)
                return ANET_ERR;
        }
    } else {
        if (anetListen(err,s,(struct sockaddr*)&sa,sizeof(sa)) == ANET_ERR)
            return ANET_ERR;
    }
    return s;
}

