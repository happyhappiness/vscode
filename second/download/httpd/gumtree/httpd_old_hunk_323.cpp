        if (cipher_list_old) {
            sk_SSL_CIPHER_free(cipher_list_old);
        }

        /* tracing */
        if (renegotiate) {
            ssl_log(r->server, SSL_LOG_TRACE,
                    "Reconfigured cipher suite will force renegotiation");
        }
    }

    /*
     * override of SSLVerifyDepth
     *
