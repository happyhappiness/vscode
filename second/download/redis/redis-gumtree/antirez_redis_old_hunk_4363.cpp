            len++;
        }
    }
    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",len));
}

static void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
