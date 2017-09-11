         * have a connected socket. Let's return to the caller. */
        goto end;
    }
    if (p == NULL) {
        anetSetError(err, "creating socket: %s", strerror(errno));
        goto error;
    }

error:
    if (s != ANET_ERR) {
