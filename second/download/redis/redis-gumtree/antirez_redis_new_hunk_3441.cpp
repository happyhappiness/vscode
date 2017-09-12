    aeDeleteFileEvent(config.el,c->context->fd,AE_READABLE);
    aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
    c->written = 0;
}

static void randomizeClientKey(client c) {
    char buf[32];
    size_t i, r;

    for (i = 0; i < c->randlen; i++) {
        r = random() % config.randomkeys_keyspacelen;
        snprintf(buf,sizeof(buf),"%012lu",r);
        memcpy(c->randptr[i],buf,12);
    }
}

static void clientDone(client c) {
