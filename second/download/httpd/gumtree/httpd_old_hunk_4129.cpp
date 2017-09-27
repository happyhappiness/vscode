            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02220)
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
     * SSLConnRec attached to the SSL* of OpenSSL.  We've to force the
     * renegotiation if the reconfigured/new verify depth is less than the
     * currently active/remembered verify depth (because this means more
     * restriction on the certificate chain).
     */
    n = (sslconn->verify_depth != UNSET) ?
        sslconn->verify_depth :
        (mySrvConfig(handshakeserver))->server->auth.verify_depth;
    /* determine the new depth */
    sslconn->verify_depth = (dc->nVerifyDepth != UNSET) ?
                            dc->nVerifyDepth : sc->server->auth.verify_depth;
    if (sslconn->verify_depth < n) {
        renegotiate = TRUE;
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02254)
                     "Reduced client verification depth will force "
                     "renegotiation");
    }

    /*
     * override of SSLVerifyClient
     *
     * We force a renegotiation if the reconfigured/new verify type is
     * stronger than the currently active verify type.
     *
     * The order is: none << optional_no_ca << optional << require
