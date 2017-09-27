        else {
            /* If the reneg buffer size is set to zero, just fail. */
            rv = HTTP_REQUEST_ENTITY_TOO_LARGE;
        }

        if (rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "could not buffer message body to allow "
                          "SSL renegotiation to proceed");
            return rv;
        }
    }

    /*
     * now do the renegotiation if anything was actually reconfigured
     */
    if (renegotiate) {
        /*
         * Now we force the SSL renegotation by sending the Hello Request
         * message to the client. Here we have to do a workaround: Actually
         * OpenSSL returns immediately after sending the Hello Request (the
         * intent AFAIK is because the SSL/TLS protocol says it's not a must
         * that the client replies to a Hello Request). But because we insist
         * on a reply (anything else is an error for us) we have to go to the
         * ACCEPT state manually. Using SSL_set_accept_state() doesn't work
         * here because it resets too much of the connection.  So we set the
         * state explicitly and continue the handshake manually.
         */
        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                      "Requesting connection re-negotiation");

        if (renegotiate_quick) {
            STACK_OF(X509) *cert_stack;

            /* perform just a manual re-verification of the peer */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                         "Performing quick renegotiation: "
                         "just re-verifying the peer");

            cert_stack = (STACK_OF(X509) *)SSL_get_peer_cert_chain(ssl);

            cert = SSL_get_peer_certificate(ssl);
