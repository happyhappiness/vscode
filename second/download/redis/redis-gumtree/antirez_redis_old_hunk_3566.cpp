    memcpy(p,buf,strlen(buf));
}

static void prepareClientForReply(client c, int type) {
    if (type == REPLY_BULK) {
        c->replytype = REPLY_BULK;
        c->readlen = -1;
    } else if (type == REPLY_MBULK) {
        c->replytype = REPLY_MBULK;
        c->readlen = -1;
        c->mbulk = -1;
    } else {
        c->replytype = type;
        c->readlen = 0;
    }
}

static void clientDone(client c) {
    static int last_tot_received = 1;

    long long latency;
    config.donerequests ++;
    latency = mstime() - c->start;
    if (latency > MAX_LATENCY) latency = MAX_LATENCY;
    config.latency[latency]++;

    if (config.debug && last_tot_received != c->totreceived) {
        printf("Tot bytes received: %d\n", c->totreceived);
        last_tot_received = c->totreceived;
    }
    if (config.donerequests == config.requests) {
        freeClient(c);
        aeStop(config.el);
