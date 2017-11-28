
#if USE_OPENSSL
    if (Config.ssl_client.foreignIntermediateCertsPath)
        Ssl::loadSquidUntrusted(Config.ssl_client.foreignIntermediateCertsPath);
#endif

#if USE_OPENSSL
    debugs(3, DBG_IMPORTANT, "Initializing https proxy context");

    Config.ssl_client.sslContext = sslCreateClientContext(Config.ssl_client.cert, Config.ssl_client.key, Config.ssl_client.version, Config.ssl_client.cipher, NULL, Config.ssl_client.flags, Config.ssl_client.cafile, Config.ssl_client.capath, Config.ssl_client.crlfile);
    // Pre-parse SSL client options to be applied when the client SSL objects created.
    // Options must not used in the case of peek or stare bump mode.
    Config.ssl_client.parsedOptions = Ssl::parse_options(::Config.ssl_client.options);
    Ssl::useSquidUntrusted(Config.ssl_client.sslContext);

    for (CachePeer *p = Config.peers; p != NULL; p = p->next) {
        if (p->use_ssl) {
            debugs(3, DBG_IMPORTANT, "Initializing cache_peer " << p->name << " SSL context");
            p->sslContext = sslCreateClientContext(p->sslcert, p->sslkey, p->sslversion, p->sslcipher, p->ssloptions, p->sslflags, p->sslcafile, p->sslcapath, p->sslcrlfile);
        }
    }

    for (AnyP::PortCfgPointer s = HttpPortList; s != NULL; s = s->next) {
        if (!s->flags.tunnelSslBumping)
            continue;

        debugs(3, DBG_IMPORTANT, "Initializing http_port " << s->s << " SSL context");
        s->configureSslServerContext();
    }

    for (AnyP::PortCfgPointer s = HttpsPortList; s != NULL; s = s->next) {
        debugs(3, DBG_IMPORTANT, "Initializing https_port " << s->s << " SSL context");
        s->configureSslServerContext();
    }

#endif

    // prevent infinite fetch loops in the request parser
    // due to buffer full but not enough data recived to finish parse
    if (Config.maxRequestBufferSize <= Config.maxRequestHeaderSize) {
        fatalf("Client request buffer of %u bytes cannot hold a request with %u bytes of headers." \
