static int anetListen(char *err, int s, struct sockaddr *sa, socklen_t len) {
    if (bind(s,sa,len) == -1) {
        anetSetError(err, "bind: %s\n", strerror(errno));
        close(s);
        return ANET_ERR;
    }
    if (listen(s, 511) == -1) { /* the magic 511 constant is from nginx */
        anetSetError(err, "listen: %s\n", strerror(errno));
        close(s);
        return ANET_ERR;
    }
    return ANET_OK;
}