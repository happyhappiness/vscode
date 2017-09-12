         * SORT result is empty a new key is set and maybe the old content
         * replaced. */
        server.dirty += 1+outputlen;
        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",outputlen));
    }

