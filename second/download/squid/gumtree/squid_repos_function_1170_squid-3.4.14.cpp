static void
parsePortSpecification(AnyP::PortCfg * s, char *token)
{
    char *host = NULL;
    unsigned short port = 0;
    char *t = NULL;
    char *junk = NULL;

    s->disable_pmtu_discovery = DISABLE_PMTU_OFF;
    s->name = xstrdup(token);
    s->connection_auth_disabled = false;

    if (*token == '[') {
        /* [ipv6]:port */
        host = token + 1;
        t = strchr(host, ']');
        if (!t) {
            debugs(3, DBG_CRITICAL, s->protocol << "_port: missing ']' on IPv6 address: " << token);
            self_destruct();
        }
        *t = '\0';
        ++t;
        if (*t != ':') {
            debugs(3, DBG_CRITICAL, s->protocol << "_port: missing Port in: " << token);
            self_destruct();
        }
        if (!Ip::EnableIpv6) {
            debugs(3, DBG_CRITICAL, "FATAL: " << s->protocol << "_port: IPv6 is not available.");
            self_destruct();
        }
        port = xatos(t + 1);
    } else if ((t = strchr(token, ':'))) {
        /* host:port */
        /* ipv4:port */
        host = token;
        *t = '\0';
        port = xatos(t + 1);

    } else if (strtol(token, &junk, 10) && !*junk) {
        port = xatos(token);
        debugs(3, 3, s->protocol << "_port: found Listen on Port: " << port);
    } else {
        debugs(3, DBG_CRITICAL, s->protocol << "_port: missing Port: " << token);
        self_destruct();
    }

    if (port == 0 && host != NULL) {
        debugs(3, DBG_CRITICAL, s->protocol << "_port: Port cannot be 0: " << token);
        self_destruct();
    }

    if (NULL == host) {
        s->s.setAnyAddr();
        s->s.port(port);
        if (!Ip::EnableIpv6)
            s->s.setIPv4();
        debugs(3, 3, s->protocol << "_port: found Listen on wildcard address: *:" << s->s.port() );
    } else if ( (s->s = host) ) { /* check/parse numeric IPA */
        s->s.port(port);
        if (!Ip::EnableIpv6)
            s->s.setIPv4();
        debugs(3, 3, s->protocol << "_port: Listen on Host/IP: " << host << " --> " << s->s);
    } else if ( s->s.GetHostByName(host) ) { /* check/parse for FQDN */
        /* dont use ipcache */
        s->defaultsite = xstrdup(host);
        s->s.port(port);
        if (!Ip::EnableIpv6)
            s->s.setIPv4();
        debugs(3, 3, s->protocol << "_port: found Listen as Host " << s->defaultsite << " on IP: " << s->s);
    } else {
        debugs(3, DBG_CRITICAL, s->protocol << "_port: failed to resolve Host/IP: " << host);
        self_destruct();
    }
}