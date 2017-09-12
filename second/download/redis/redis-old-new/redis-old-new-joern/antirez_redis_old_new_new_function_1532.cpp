void latencyCommand(redisClient *c) {
    struct latencyTimeSeries *ts;

    if (!strcasecmp(c->argv[1]->ptr,"samples") && c->argc == 3) {
        /* LATENCY SAMPLES <event> */
        ts = dictFetchValue(server.latency_events,c->argv[2]->ptr);
        if (ts == NULL) goto nodataerr;
        latencyCommandReplyWithSamples(c,ts);
    } else {
        addReply(c,shared.syntaxerr);
        return;
    }
    return;

nodataerr:
    /* Common error when the user asks for an event we have no latency
     * information about. */
    addReplyErrorFormat(c,
        "No samples available for event '%s'", c->argv[2]->ptr);
}