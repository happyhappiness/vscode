                    return REDIS_ERR;
                }

                bulklen = strtol(c->querybuf+pos+1,&eptr,10);
                tolerr = (eptr[0] != '\r');
                if (tolerr || bulklen == LONG_MIN || bulklen == LONG_MAX ||
                    bulklen < 0 || bulklen > 512*1024*1024)
                {
                    addReplyError(c,"Protocol error: invalid bulk length");
                    setProtocolError(c,pos);
                    return REDIS_ERR;
                }
                pos += eptr-(c->querybuf+pos)+2;
                c->bulklen = bulklen;
            } else {
                /* No newline in current buffer, so wait for more data */
                break;
