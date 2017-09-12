    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bindaddr && inet_aton(bindaddr, &sa.sin_addr) == 0) {
        anetSetError(err, "Invalid bind address\n");
        close(s);
        return ANET_ERR;
    }
