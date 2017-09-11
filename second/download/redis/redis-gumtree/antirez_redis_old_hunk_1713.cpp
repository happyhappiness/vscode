    buf[0] = '\0';
    if (anetPeerToString(c->fd,ip,sizeof(ip),NULL) != -1) {
        if (c->slave_listening_port)
            snprintf(buf,sizeof(buf),"%s:%d",ip,c->slave_listening_port);
        else
            snprintf(buf,sizeof(buf),"%s:<unknown-slave-port>",ip);
    } else {
