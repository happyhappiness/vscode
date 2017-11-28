int
getMyPort(void)
{
    AnyP::PortCfg *p = NULL;
    if ((p = Config.Sockaddr.http)) {
        // skip any special interception ports
        while (p && p->flags.isIntercepted())
            p = p->next;
        if (p)
            return p->s.port();
    }

#if USE_SSL
    if ((p = Config.Sockaddr.https)) {
        // skip any special interception ports
        while (p && p->flags.isIntercepted())
            p = p->next;
        if (p)
            return p->s.port();
    }
#endif

    debugs(21, DBG_CRITICAL, "ERROR: No forward-proxy ports configured.");
    return 0; // Invalid port. This will result in invalid URLs on bad configurations.
}