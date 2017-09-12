    aeDeleteFileEvent(config.el,c->context->fd,AE_READABLE);
    aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
    c->written = 0;
    c->state = CLIENT_SENDQUERY;
    c->start = ustime();
    c->latency = -1;
}

static void randomizeClientKey(client c) {
    char *p;
    char buf[32];
    long r;

    p = strstr(c->obuf, "_rand");
    if (!p) return;
    p += 5;
    r = random() % config.randomkeys_keyspacelen;
    sprintf(buf,"%ld",r);
    memcpy(p,buf,strlen(buf));
}

static void clientDone(client c) {
