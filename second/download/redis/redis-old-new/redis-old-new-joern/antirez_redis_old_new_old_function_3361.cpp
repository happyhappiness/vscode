static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask)
{
    char buf[1024], *p;
    int nread, pos=0, len=0;
    client c = privdata;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(fd);
    REDIS_NOTUSED(mask);

    nread = read(c->fd,buf,sizeof(buf));
    if (nread == -1) {
        fprintf(stderr, "Reading from socket: %s\n", strerror(errno));
        freeClient(c);
        return;
    }
    if (nread == 0) {
        fprintf(stderr, "EOF from client\n");
        freeClient(c);
        return;
    }
    c->totreceived += nread;
    c->ibuf = sdscatlen(c->ibuf,buf,nread);
    len = sdslen(c->ibuf);

    if (c->replytype == REPLY_INT ||
        c->replytype == REPLY_RETCODE)
    {
        /* Check if the first line is complete. This is everything we need
         * when waiting for an integer or status code reply.*/
        if ((p = strstr(c->ibuf,"\r\n")) != NULL)
            goto done;
    } else if (c->replytype == REPLY_BULK) {
        int advance = 0;
        if (c->readlen < 0) {
            advance = readLen(c->ibuf+pos,&c->readlen);
            if (advance) {
                pos += advance;
                if (c->readlen == -1) {
                    goto done;
                } else {
                    /* include the trailing \r\n */
                    c->readlen += 2;
                }
            } else {
                goto skip;
            }
        }

        int canconsume;
        if (c->readlen > 0) {
            canconsume = c->readlen > (len-pos) ? (len-pos) : c->readlen;
            c->readlen -= canconsume;
            pos += canconsume;
        }

        if (c->readlen == 0)
            goto done;
    } else if (c->replytype == REPLY_MBULK) {
        int advance = 0;
        if (c->mbulk == -1) {
            advance = readLen(c->ibuf+pos,&c->mbulk);
            if (advance) {
                pos += advance;
                if (c->mbulk == -1)
                    goto done;
            } else {
                goto skip;
            }
        }

        int canconsume;
        while(c->mbulk > 0 && pos < len) {
            if (c->readlen > 0) {
                canconsume = c->readlen > (len-pos) ? (len-pos) : c->readlen;
                c->readlen -= canconsume;
                pos += canconsume;
                if (c->readlen == 0)
                    c->mbulk--;
            } else {
                advance = readLen(c->ibuf+pos,&c->readlen);
                if (advance) {
                    pos += advance;
                    if (c->readlen == -1) {
                        c->mbulk--;
                        continue;
                    } else {
                        /* include the trailing \r\n */
                        c->readlen += 2;
                    }
                } else {
                    goto skip;
                }
            }
        }

        if (c->mbulk == 0)
            goto done;
    }

skip:
    c->ibuf = sdsrange(c->ibuf,pos,-1);
    return;
done:
    clientDone(c);
    return;
}