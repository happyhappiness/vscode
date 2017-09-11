        sdsfree(buf);
        matches++;
    }
    if (stringmatch(pattern,"unixsocketperm",0)) {
        char buf[32];
        snprintf(buf,sizeof(buf),"%o",server.unixsocketperm);
        addReplyBulkCString(c,"unixsocketperm");
        addReplyBulkCString(c,buf);
        matches++;
    }
    if (stringmatch(pattern,"slaveof",0)) {
        char buf[256];

        addReplyBulkCString(c,"slaveof");
