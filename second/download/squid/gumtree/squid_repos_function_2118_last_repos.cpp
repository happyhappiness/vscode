int
getMyPort(void)
{
    AnyP::PortCfgPointer p;
    if ((p = HttpPortList) != NULL) {
        // skip any special interception ports
        while (p != NULL && p->flags.isIntercepted())
            p = p->next;
        if (p != NULL)
            return p->s.port();
    }

    if ((p = FtpPortList) != NULL) {
        // skip any special interception ports
        while (p != NULL && p->flags.isIntercepted())
            p = p->next;
        if (p != NULL)
            return p->s.port();
    }

    debugs(21, DBG_CRITICAL, "ERROR: No forward-proxy ports configured.");
    return 0; // Invalid port. This will result in invalid URLs on bad configurations.
}