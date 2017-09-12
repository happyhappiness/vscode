    if (stringmatch(pattern,"maxmemory",0)) {
        char buf[128];

        snprintf(buf,128,"%llu\n",server.maxmemory);
        addReplyBulkCString(c,"maxmemory");
        addReplyBulkCString(c,buf);
        matches++;
    }
    if (stringmatch(pattern,"appendfsync",0)) {
        char *policy;

