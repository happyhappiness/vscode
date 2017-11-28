static void
dump_generic_port(StoreEntry * e, const char *n, const AnyP::PortCfgPointer &s)
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

    else if (s->flags.proxySurrogate)
        storeAppendPrintf(e, " require-proxy-header");

    else if (s->flags.accelSurrogate) {
        storeAppendPrintf(e, " accel");

        if (s->vhost)
            storeAppendPrintf(e, " vhost");

        if (s->vport < 0)
            storeAppendPrintf(e, " vport");
        else if (s->vport > 0)
            storeAppendPrintf(e, " vport=%d", s->vport);

        if (s->defaultsite)
            storeAppendPrintf(e, " defaultsite=%s", s->defaultsite);

        // TODO: compare against prefix of 'n' instead of assuming http_port
        if (s->transport.protocol != AnyP::PROTO_HTTP)
            storeAppendPrintf(e, " protocol=%s", AnyP::ProtocolType_str[s->transport.protocol]);

        if (s->allow_direct)
            storeAppendPrintf(e, " allow-direct");

        if (s->ignore_cc)
            storeAppendPrintf(e, " ignore-cc");

    }

    // Generic independent options

    if (s->name)
        storeAppendPrintf(e, " name=%s", s->name);

#if USE_HTTP_VIOLATIONS
    if (!s->flags.accelSurrogate && s->ignore_cc)
        storeAppendPrintf(e, " ignore-cc");
#endif

    if (s->connection_auth_disabled)
        storeAppendPrintf(e, " connection-auth=off");
    else
        storeAppendPrintf(e, " connection-auth=on");

    if (s->disable_pmtu_discovery != DISABLE_PMTU_OFF) {
        const char *pmtu;

        if (s->disable_pmtu_discovery == DISABLE_PMTU_ALWAYS)
            pmtu = "always";
        else
            pmtu = "transparent";

        storeAppendPrintf(e, " disable-pmtu-discovery=%s", pmtu);
    }

    if (s->s.isAnyAddr() && !s->s.isIPv6())
        storeAppendPrintf(e, " ipv4");

    if (s->tcp_keepalive.enabled) {
        if (s->tcp_keepalive.idle || s->tcp_keepalive.interval || s->tcp_keepalive.timeout) {
            storeAppendPrintf(e, " tcpkeepalive=%d,%d,%d", s->tcp_keepalive.idle, s->tcp_keepalive.interval, s->tcp_keepalive.timeout);
        } else {
            storeAppendPrintf(e, " tcpkeepalive");
        }
    }

#if USE_OPENSSL
    if (s->flags.tunnelSslBumping)
        storeAppendPrintf(e, " ssl-bump");
#endif

    s->secure.dumpCfg(e, "tls-");

#if USE_OPENSSL
    if (s->sslContextSessionId)
        storeAppendPrintf(e, " sslcontext=%s", s->sslContextSessionId);

    if (!s->generateHostCertificates)
        storeAppendPrintf(e, " generate-host-certificates=off");

    if (s->dynamicCertMemCacheSize != 4*1024*1024) // 4MB default
        storeAppendPrintf(e, "dynamic_cert_mem_cache_size=%" PRIuSIZE "%s\n", s->dynamicCertMemCacheSize, B_BYTES_STR);
#endif
}