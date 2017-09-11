    }

    if (!strcasecmp(c->argv[1]->ptr,"meet") && c->argc == 4) {
        long port;

        if (getLongFromObjectOrReply(c, c->argv[3], &port, NULL) != REDIS_OK) {
            addReplyError(c,"Invalid TCP port specified");
            return;
        }

        if (clusterStartHandshake(c->argv[2]->ptr,port) == 0 &&
            errno == EINVAL)
        {
            addReplyError(c,"Invalid node address specified");
        } else {
            addReply(c,shared.ok);
        }
