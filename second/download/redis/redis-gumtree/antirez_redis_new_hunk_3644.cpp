        if (c->multibulklen <= 0) {
            c->querybuf = sdsrange(c->querybuf,pos,-1);
            return REDIS_OK;
        } else if (c->multibulklen > 1024*1024) {
            addReplyError(c,"Protocol error: invalid multibulk length");
            setProtocolError(c,pos);
            return REDIS_ERR;
        }

        /* Setup argv array on client structure */
