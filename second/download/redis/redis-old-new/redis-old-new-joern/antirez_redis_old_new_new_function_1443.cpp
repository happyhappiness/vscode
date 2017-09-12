char *replicationGetSlaveName(redisClient *c) {
    static char buf[REDIS_PEER_ID_LEN];
    char ip[REDIS_IP_STR_LEN];

    ip[0] = '\0';
    buf[0] = '\0';
    if (anetPeerToString(c->fd,ip,sizeof(ip),NULL) != -1) {
        if (c->slave_listening_port)
            snprintf(buf,sizeof(buf),"%s:%d",ip,c->slave_listening_port);
        else
            snprintf(buf,sizeof(buf),"%s:<unknown-slave-port>",ip);
    } else {
        snprintf(buf,sizeof(buf),"client id #%llu",
            (unsigned long long) c->id);
    }
    return buf;
}