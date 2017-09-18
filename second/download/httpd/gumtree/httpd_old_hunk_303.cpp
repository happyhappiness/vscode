
    /*
     * Some information about the certificate(s)
     */

    if (SSL_X509_isSGC(cert)) {
        ssl_log(s, SSL_LOG_INFO|SSL_INIT,
                "%s server certificate enables "
                "Server Gated Cryptography (SGC)", 
                ssl_asn1_keystr(type));
    }

    if (SSL_X509_getBC(cert, &is_ca, &pathlen)) {
        if (is_ca) {
            ssl_log(s, SSL_LOG_WARN|SSL_INIT,
                    "%s server certificate is a CA certificate "
                    "(BasicConstraints: CA == TRUE !?)",
                    ssl_asn1_keystr(type));
        }

        if (pathlen > 0) {
            ssl_log(s, SSL_LOG_WARN|SSL_INIT,
                    "%s server certificate is not a leaf certificate "
                    "(BasicConstraints: pathlen == %d > 0 !?)",
                    ssl_asn1_keystr(type), pathlen);
        }
    }

    if (SSL_X509_getCN(ptemp, cert, &cn)) {
        int fnm_flags = FNM_PERIOD|FNM_CASE_BLIND;

        if (apr_is_fnmatch(cn) &&
            (apr_fnmatch(cn, s->server_hostname,
                         fnm_flags) == FNM_NOMATCH))
        {
            ssl_log(s, SSL_LOG_WARN|SSL_INIT,
                    "%s server certificate wildcard CommonName (CN) `%s' "
                    "does NOT match server name!?",
                    ssl_asn1_keystr(type), cn);
        }
        else if (strNE(s->server_hostname, cn)) {
            ssl_log(s, SSL_LOG_WARN|SSL_INIT,
                    "%s server certificate CommonName (CN) `%s' "
                    "does NOT match server name!?",
                    ssl_asn1_keystr(type), cn);
        }
    }
}

static void ssl_init_server_certs(server_rec *s,
                                  apr_pool_t *p,
