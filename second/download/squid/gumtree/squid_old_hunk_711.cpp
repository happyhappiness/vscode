    }

    contextMethod = Ssl::contextMethod(version);
    if (!contextMethod)
        fatalf("Unable to compute context method to use");

    if (dhfile)
        dhParams.reset(Ssl::readDHParams(dhfile));

    if (sslflags)
        sslContextFlags = Ssl::parse_flags(sslflags);

    sslOptions = Ssl::parse_options(options);

    staticSslContext.reset(sslCreateServerContext(*this));

    if (!staticSslContext) {
        char buf[128];
        fatalf("%s_port %s initialization error", protocol,  s.toUrl(buf, sizeof(buf)));
    }
}
#endif

