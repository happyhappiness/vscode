void
Security::PeerOptions::parse(const char *token)
{
    if (!*token) {
        // config says just "ssl" or "tls" (or "tls-")
        encryptTransport = true;
        return;
    }

    if (strncmp(token, "disable", 7) == 0) {
        clear();
        return;
    }

    if (strncmp(token, "cert=", 5) == 0) {
        KeyData t;
        t.privateKeyFile = t.certFile = SBuf(token + 5);
        certs.emplace_back(t);
    } else if (strncmp(token, "key=", 4) == 0) {
        if (certs.empty() || certs.back().certFile.isEmpty()) {
            fatal("cert= option must be set before key= is used.");
            return;
        }
        KeyData &t = certs.back();
        t.privateKeyFile = SBuf(token + 4);
    } else if (strncmp(token, "version=", 8) == 0) {
        debugs(0, DBG_PARSE_NOTE(1), "UPGRADE WARNING: SSL version= is deprecated. Use options= to limit protocols instead.");
        sslVersion = xatoi(token + 8);
    } else if (strncmp(token, "min-version=", 12) == 0) {
        tlsMinVersion = SBuf(token + 12);
    } else if (strncmp(token, "options=", 8) == 0) {
        sslOptions = SBuf(token + 8);
        parseOptions();
    } else if (strncmp(token, "cipher=", 7) == 0) {
        sslCipher = SBuf(token + 7);
    } else if (strncmp(token, "cafile=", 7) == 0) {
        caFiles.emplace_back(SBuf(token + 7));
    } else if (strncmp(token, "capath=", 7) == 0) {
        caDir = SBuf(token + 7);
#if !USE_OPENSSL
        debugs(3, DBG_PARSE_NOTE(1), "WARNING: capath= option requires --with-openssl.");
#endif
    } else if (strncmp(token, "crlfile=", 8) == 0) {
        crlFile = SBuf(token + 8);
        loadCrlFile();
    } else if (strncmp(token, "flags=", 6) == 0) {
        if (parsedFlags != 0) {
            debugs(3, DBG_PARSE_NOTE(1), "WARNING: Overwriting flags=" << sslFlags << " with " << SBuf(token + 6));
        }
        sslFlags = SBuf(token + 6);
        parsedFlags = parseFlags();
    } else if (strncmp(token, "default-ca=off", 14) == 0 || strncmp(token, "no-default-ca", 13) == 0) {
        if (flags.tlsDefaultCa.configured() && flags.tlsDefaultCa)
            fatalf("ERROR: previous default-ca settings conflict with %s", token);
        flags.tlsDefaultCa.configure(false);
    } else if (strncmp(token, "default-ca=on", 13) == 0 || strncmp(token, "default-ca", 10) == 0) {
        if (flags.tlsDefaultCa.configured() && !flags.tlsDefaultCa)
            fatalf("ERROR: previous default-ca settings conflict with %s", token);
        flags.tlsDefaultCa.configure(true);
    } else if (strncmp(token, "domain=", 7) == 0) {
        sslDomain = SBuf(token + 7);
    } else if (strncmp(token, "no-npn", 6) == 0) {
        flags.tlsNpn = false;
    } else {
        debugs(3, DBG_CRITICAL, "ERROR: Unknown TLS option '" << token << "'");
        return;
    }

    encryptTransport = true;
}