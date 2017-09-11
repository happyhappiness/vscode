        char buf2[1024];

        /* Read the two replies */
        if (select && syncReadLine(cs->fd, buf1, sizeof(buf1), timeout) <= 0)
            goto socket_rd_err;
        if (syncReadLine(cs->fd, buf2, sizeof(buf2), timeout) <= 0)
            goto socket_rd_err;
        if ((select && buf1[0] == '-') || buf2[0] == '-') {
            /* On error assume that last_dbid is no longer valid. */
            cs->last_dbid = -1;
            addReplyErrorFormat(c,"Target instance replied with error: %s",
                (cs->last_dbid != dbid && buf1[0] == '-') ? buf1+1 : buf2+1);
