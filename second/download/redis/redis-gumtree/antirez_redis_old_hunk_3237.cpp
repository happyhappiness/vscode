        /* Setup argv array on client structure */
        if (c->argv) zfree(c->argv);
        c->argv = zmalloc(sizeof(robj*)*c->multibulklen);

        /* Search new newline */
        newline = strchr(c->querybuf+pos,'\r');
    }

    redisAssert(c->multibulklen > 0);
    while(c->multibulklen) {
        /* Read bulk length if unknown */
        if (c->bulklen == -1) {
            newline = strchr(c->querybuf+pos,'\r');
            if (newline != NULL) {
                if (c->querybuf[pos] != '$') {
                    addReplyErrorFormat(c,
                        "Protocol error: expected '$', got '%c'",
                        c->querybuf[pos]);
                    setProtocolError(c,pos);
                    return REDIS_ERR;
                }

                ok = string2ll(c->querybuf+pos+1,newline-(c->querybuf+pos+1),&ll);
                if (!ok || ll < 0 || ll > 512*1024*1024) {
                    addReplyError(c,"Protocol error: invalid bulk length");
                    setProtocolError(c,pos);
                    return REDIS_ERR;
                }
                pos += newline-(c->querybuf+pos)+2;
                c->bulklen = ll;
            } else {
                /* No newline in current buffer, so wait for more data */
                break;
            }
        }

        /* Read bulk argument */
