        close(s);
        return ANET_ERR;
    }
    if (listen(s, 64) == -1) {
        anetSetError(err, "listen: %s\n", strerror(errno));
        close(s);
        return ANET_ERR;
