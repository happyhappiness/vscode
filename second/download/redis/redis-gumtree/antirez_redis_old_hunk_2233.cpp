
    /* Try to obtain our own IP address. */
    if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) == -1) return REDIS_ERR;
    if (ri->flags & SRI_DISCONNECTED) return;

    /* Format and send the Hello message. */
    snprintf(payload,sizeof(payload),
