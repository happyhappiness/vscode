    }
}

void sendReplyToClientWritev(aeEventLoop *el, int fd, void *privdata, int mask)
{
    redisClient *c = privdata;
    int nwritten = 0, totwritten = 0, objlen, willwrite;
    robj *o;
    struct iovec iov[REDIS_WRITEV_IOVEC_COUNT];
    int offset, ion = 0;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(mask);

    listNode *node;
    while (listLength(c->reply)) {
        offset = c->sentlen;
        ion = 0;
        willwrite = 0;

        /* fill-in the iov[] array */
        for(node = listFirst(c->reply); node; node = listNextNode(node)) {
            o = listNodeValue(node);
            objlen = sdslen(o->ptr);

            if (totwritten + objlen - offset > REDIS_MAX_WRITE_PER_EVENT)
                break;

            if(ion == REDIS_WRITEV_IOVEC_COUNT)
                break; /* no more iovecs */

            iov[ion].iov_base = ((char*)o->ptr) + offset;
            iov[ion].iov_len = objlen - offset;
            willwrite += objlen - offset;
            offset = 0; /* just for the first item */
            ion++;
        }

        if(willwrite == 0)
            break;

        /* write all collected blocks at once */
        if((nwritten = writev(fd, iov, ion)) < 0) {
            if (errno != EAGAIN) {
                redisLog(REDIS_VERBOSE,
                         "Error writing to client: %s", strerror(errno));
                freeClient(c);
                return;
            }
            break;
        }

        totwritten += nwritten;
        offset = c->sentlen;

        /* remove written robjs from c->reply */
        while (nwritten && listLength(c->reply)) {
            o = listNodeValue(listFirst(c->reply));
            objlen = sdslen(o->ptr);

            if(nwritten >= objlen - offset) {
                listDelNode(c->reply, listFirst(c->reply));
                nwritten -= objlen - offset;
                c->sentlen = 0;
            } else {
                /* partial write */
                c->sentlen += nwritten;
                break;
            }
            offset = 0;
        }
    }

    if (totwritten > 0)
        c->lastinteraction = time(NULL);

    if (listLength(c->reply) == 0) {
        c->sentlen = 0;
        aeDeleteFileEvent(server.el,c->fd,AE_WRITABLE);
    }
}

/* resetClient prepare the client to process the next command */
void resetClient(redisClient *c) {
    freeClientArgv(c);
