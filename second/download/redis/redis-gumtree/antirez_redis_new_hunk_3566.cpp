    memcpy(p,buf,strlen(buf));
}

static void clientDone(client c) {
    if (config.donerequests == config.requests) {
        freeClient(c);
        aeStop(config.el);
