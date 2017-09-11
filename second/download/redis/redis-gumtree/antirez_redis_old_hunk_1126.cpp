
        if (c->argc != 6) goto numargserr;
        if (getLongFromObjectOrReply(c,c->argv[5],&quorum,"Invalid quorum")
            != REDIS_OK) return;
        if (getLongFromObjectOrReply(c,c->argv[4],&port,"Invalid port")
            != REDIS_OK) return;

        if (quorum <= 0) {
            addReplyError(c, "Quorum must be 1 or greater.");
