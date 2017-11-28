dump_generic_port(StoreEntry * e, const char *n, const AnyP::PortCfg * s)
{
    char buf[MAX_IPSTRLEN];

    storeAppendPrintf(e, "%s %s",
                      n,
                      s->s.ToURL(buf,MAX_IPSTRLEN));

    // MODES and specific sub-options.
    if (s->intercepted)
        storeAppendPrintf(e, " intercept");

    else if (s->spoof_client_ip)
        storeAppendPrintf(e, " tproxy");

    else if (s->accel) {
        storeAppendPrintf(e, " accel");

        if (s->vhost)
            storeAppendPrintf(e, " vhost");

        if (s->vport < 0)
