            len++;
        }
    }
    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",len));
}

static void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
