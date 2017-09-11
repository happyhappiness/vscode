        serverLog(LL_VERBOSE, "Client closed connection");
        freeClient(c);
        return;
    }

    sdsIncrLen(c->querybuf,nread);
    c->lastinteraction = server.unixtime;
    if (c->flags & CLIENT_MASTER) {
        c->reploff += nread;
        replicationFeedSlavesFromMasterStream(server.slaves,
                c->querybuf+qblen,nread);
    }
    server.stat_net_input_bytes += nread;
    if (sdslen(c->querybuf) > server.client_max_querybuf_len) {
        sds ci = catClientInfoString(sdsempty(),c), bytes = sdsempty();
