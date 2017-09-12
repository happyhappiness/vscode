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
