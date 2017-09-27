     * OpenSSL about the currently verify depth. Instead we remember it in our
     * SSLConnRec attached to the SSL* of OpenSSL.  We've to force the
     * renegotiation if the reconfigured/new verify depth is less than the
     * currently active/remembered verify depth (because this means more
     * restriction on the certificate chain).
     */
    n = sslconn->verify_depth ?
        sslconn->verify_depth :
        (mySrvConfig(handshakeserver))->server->auth.verify_depth;
    /* determine the new depth */
    sslconn->verify_depth = (dc->nVerifyDepth != UNSET) ?
                            dc->nVerifyDepth : sc->server->auth.verify_depth;
    if (sslconn->verify_depth < n) {
        renegotiate = TRUE;
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                     "Reduced client verification depth will force "
                     "renegotiation");
    }

    /*
     * override of SSLVerifyClient
