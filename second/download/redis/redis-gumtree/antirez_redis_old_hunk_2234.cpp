
    /* Try to obtain our own IP address. */
    if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) == -1) return REDIS_ERR;

    /* Format and send the Hello message. */
    snprintf(payload,sizeof(payload),
