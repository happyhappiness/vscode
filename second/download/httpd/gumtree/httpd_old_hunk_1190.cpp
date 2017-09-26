
        /* cleanup */
        if (cipher_list_old) {
            sk_SSL_CIPHER_free(cipher_list_old);
        }

        /* tracing */
        if (renegotiate) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "Reconfigured cipher suite will force renegotiation");
        }
    }

    /*
     * override of SSLVerifyDepth
     *
     * The depth checks are handled by us manually inside the verify callback
     * function and not by OpenSSL internally (and our function is aware of
     * both the per-server and per-directory contexts). So we cannot ask
     * OpenSSL about the currently verify depth. Instead we remember it in our
     * ap_ctx attached to the SSL* of OpenSSL.  We've to force the
     * renegotiation if the reconfigured/new verify depth is less than the
     * currently active/remembered verify depth (because this means more
     * restriction on the certificate chain).
     */
    if (dc->nVerifyDepth != UNSET) {
        /* XXX: doesnt look like sslconn->verify_depth is actually used */
        if (!(n = sslconn->verify_depth)) {
            sslconn->verify_depth = n = sc->server->auth.verify_depth;
        }

        /* determine whether a renegotiation has to be forced */
        if (dc->nVerifyDepth < n) {
            renegotiate = TRUE;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "Reduced client verification depth will force "
                         "renegotiation");
        }
    }

    /*
     * override of SSLVerifyClient
     *
     * We force a renegotiation if the reconfigured/new verify type is
