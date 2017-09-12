        if (c->multibulklen <= 0) {
            c->querybuf = sdsrange(c->querybuf,pos,-1);
            return REDIS_OK;
        }

        /* Setup argv array on client structure */
