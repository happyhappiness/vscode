dump_generic_port(StoreEntry * e, const char *n, const AnyP::PortCfg * s)
{
    char buf[MAX_IPSTRLEN];

    storeAppendPrintf(e, "%s %s",
                      n,
                      s->s.toUrl(buf,MAX_IPSTRLEN));

    // MODES and specific sub-options.
    if (s->flags.natIntercept)
        storeAppendPrintf(e, " intercept");

    else if (s->flags.tproxyIntercept)
        storeAppendPrintf(e, " tproxy");

    else if (s->flags.accelSurrogate) {
        storeAppendPrintf(e, " accel");

        if (s->vhost)
            storeAppendPrintf(e, " vhost");

        if (s->vport < 0)
