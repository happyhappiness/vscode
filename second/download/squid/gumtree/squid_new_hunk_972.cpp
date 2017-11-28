
#if USE_OPENSSL
    if (Config.ssl_client.foreignIntermediateCertsPath)
        Ssl::loadSquidUntrusted(Config.ssl_client.foreignIntermediateCertsPath);
#endif

    if (Security::ProxyOutgoingConfig.encryptTransport) {
        debugs(3, DBG_IMPORTANT, "Initializing https:// proxy context");
        Config.ssl_client.sslContext = Security::ProxyOutgoingConfig.createClientContext(false);
        if (!Config.ssl_client.sslContext) {
#if USE_OPENSSL
            fatal("ERROR: Could not initialize https:// proxy context");
#else
            debugs(3, DBG_IMPORTANT, "ERROR: proxying https:// currently still requires --with-openssl");
#endif
        }
#if USE_OPENSSL
        Ssl::useSquidUntrusted(Config.ssl_client.sslContext.get());
#endif
    }

    for (CachePeer *p = Config.peers; p != NULL; p = p->next) {

        // default value for ssldomain= is the peer host/IP
        if (p->secure.sslDomain.isEmpty())
            p->secure.sslDomain = p->host;

        if (p->secure.encryptTransport) {
            debugs(3, DBG_IMPORTANT, "Initializing cache_peer " << p->name << " TLS context");
            p->sslContext = p->secure.createClientContext(true);
            if (!p->sslContext) {
                debugs(3, DBG_CRITICAL, "ERROR: Could not initialize cache_peer " << p->name << " TLS context");
                self_destruct();
                return;
            }
        }
    }

#if USE_OPENSSL
    for (AnyP::PortCfgPointer s = HttpPortList; s != NULL; s = s->next) {
        if (!s->secure.encryptTransport)
            continue;
        debugs(3, DBG_IMPORTANT, "Initializing " << AnyP::UriScheme(s->transport.protocol) << "_port " << s->s << " TLS context");
        s->configureSslServerContext();
    }
#endif

    // prevent infinite fetch loops in the request parser
    // due to buffer full but not enough data recived to finish parse
    if (Config.maxRequestBufferSize <= Config.maxRequestHeaderSize) {
        fatalf("Client request buffer of %u bytes cannot hold a request with %u bytes of headers." \
