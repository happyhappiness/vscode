
    /* For slaves and sentinel we use ip:port as name. */
    if (flags & (SRI_SLAVE|SRI_SENTINEL)) {
        anetFormatIP(slavename, sizeof(slavename), hostname, port);
        name = slavename;
    }

