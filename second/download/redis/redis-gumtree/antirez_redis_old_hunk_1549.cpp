        sdsfree(name);
        addReplyErrorFormat(c,"Can't connect to target node: %s",
            server.neterr);
        return -1;
    }
    anetEnableTcpNoDelay(server.neterr,fd);

