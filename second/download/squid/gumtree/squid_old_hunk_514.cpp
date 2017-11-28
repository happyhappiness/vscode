    sslOptions = Ssl::parse_options(options);

    staticSslContext.reset(sslCreateServerContext(*this));

    if (!staticSslContext) {
        char buf[128];
        fatalf("%s_port %s initialization error", protocol,  s.ToURL(buf, sizeof(buf)));
    }
}
#endif

