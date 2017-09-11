            return;
        }
        if (rewriteConfig(server.configfile) == -1) {
            addReplyErrorFormat(c,"Rewriting config file: %s", strerror(errno));
        } else {
            addReply(c,shared.ok);
