        if (c->argc != 2) goto badarity;
        if (server.configfile == NULL) {
            addReplyError(c,"The server is running without a config file");
            return;
        }
        if (rewriteConfig(server.configfile) == -1) {
            addReplyErrorFormat(c,"Rewriting config file: %s", strerror(errno));
        } else {
            addReply(c,shared.ok);
        }
    } else {
        addReplyError(c,
