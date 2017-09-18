            sslconn->verify_depth = n = sc->server->auth.verify_depth;
        }

        /* determine whether a renegotiation has to be forced */
        if (dc->nVerifyDepth < n) {
            renegotiate = TRUE;
            ssl_log(r->server, SSL_LOG_TRACE,
                    "Reduced client verification depth "
                    "will force renegotiation");
        }
    }

    /*
     * override of SSLVerifyClient
     *
