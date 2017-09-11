        if (errno == EINPROGRESS && !blocking) {
            /* This is ok. */
        } else {
            __redisSetError(c,REDIS_ERR_IO,NULL);
            close(s);
            return REDIS_ERR;
        }
    }

    c->fd = s;
    c->flags |= REDIS_CONNECTED;
    return REDIS_OK;
