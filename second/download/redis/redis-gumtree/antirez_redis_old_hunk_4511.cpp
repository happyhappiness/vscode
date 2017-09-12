        close(s);
        return ANET_ERR;
    }
    if (listen(s, 32) == -1) {
        anetSetError(err, "listen: %s\n", strerror(errno));
        close(s);
        return ANET_ERR;
