    } else if (c->multibulk) {
        if (c->bulklen == -1) {
            if (((char*)c->argv[0]->ptr)[0] != '$') {
                addReplyError(c,"multi bulk protocol error");
                resetClient(c);
                return 1;
            } else {
                char *eptr;
                long bulklen = strtol(((char*)c->argv[0]->ptr)+1,&eptr,10);
                int perr = eptr[0] != '\0';

                decrRefCount(c->argv[0]);
                if (perr || bulklen == LONG_MIN || bulklen == LONG_MAX ||
                    bulklen < 0 || bulklen > 1024*1024*1024)
                {
                    c->argc--;
                    addReplyError(c,"invalid bulk write count");
                    resetClient(c);
                    return 1;
                }
