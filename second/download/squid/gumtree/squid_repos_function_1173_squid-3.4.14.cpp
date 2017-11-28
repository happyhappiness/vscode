static void
parsePortCfg(AnyP::PortCfg ** head, const char *optionName)
{
    const char *protocol = NULL;
    if (strcmp(optionName, "http_port") == 0 ||
            strcmp(optionName, "ascii_port") == 0)
        protocol = "http";
    else if (strcmp(optionName, "https_port") == 0)
        protocol = "https";
    if (!protocol) {
        self_destruct();
        return;
    }

    char *token = strtok(NULL, w_space);

    if (!token) {
        self_destruct();
        return;
    }

    AnyP::PortCfg *s = new AnyP::PortCfg(protocol);
    parsePortSpecification(s, token);

    /* parse options ... */
    while ((token = strtok(NULL, w_space))) {
        parse_port_option(s, token);
    }

#if USE_SSL
    if (strcmp(protocol, "https") == 0) {
        /* ssl-bump on https_port configuration requires either tproxy or intercept, and vice versa */
        const bool hijacked = s->flags.isIntercepted();
        if (s->flags.tunnelSslBumping && !hijacked) {
            debugs(3, DBG_CRITICAL, "FATAL: ssl-bump on https_port requires tproxy/intercept which is missing.");
            self_destruct();
        }
        if (hijacked && !s->flags.tunnelSslBumping) {
            debugs(3, DBG_CRITICAL, "FATAL: tproxy/intercept on https_port requires ssl-bump which is missing.");
            self_destruct();
        }
    }
#endif

    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && s->s.isAnyAddr()) {
        // clone the port options from *s to *(s->next)
        s->next = cbdataReference(s->clone());
        s->next->s.setIPv4();
        debugs(3, 3, protocol << "_port: clone wildcard address for split-stack: " << s->s << " and " << s->next->s);
    }

    while (*head)
        head = &(*head)->next;

    *head = cbdataReference(s);
}