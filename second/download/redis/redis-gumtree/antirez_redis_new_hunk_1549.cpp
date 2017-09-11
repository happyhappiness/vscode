        sdsfree(name);
        addReplyErrorFormat(c,"Can't connect to target node: %s",
            server.neterr);
        return NULL;
    }
    anetEnableTcpNoDelay(server.neterr,fd);

