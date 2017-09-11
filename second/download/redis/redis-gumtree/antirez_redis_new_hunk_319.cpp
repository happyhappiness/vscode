        sdsfree(buf);
        matches++;
    }
    if (stringmatch(pattern,"unixsocketperm",1)) {
        char buf[32];
        snprintf(buf,sizeof(buf),"%o",server.unixsocketperm);
        addReplyBulkCString(c,"unixsocketperm");
        addReplyBulkCString(c,buf);
        matches++;
    }
    if (stringmatch(pattern,"slaveof",1)) {
        char buf[256];

        addReplyBulkCString(c,"slaveof");
