int ssl_hook_Access(request_rec *r)
{
    SSLDirConfigRec *dc = myDirConfig(r);
    SSLSrvConfigRec *sc = mySrvConfig(r->server);
    SSLConnRec *sslconn = myConnConfig(r->connection);
    SSL *ssl            = sslconn ? sslconn->ssl : NULL;
    SSL_CTX *ctx = NULL;
    apr_array_header_t *requires;
    ssl_require_t *ssl_requires;
    char *cp;
    int ok, i;
    BOOL renegotiate = FALSE, renegotiate_quick = FALSE;
    X509 *cert;
    X509 *peercert;
    X509_STORE *cert_store = NULL;
    X509_STORE_CTX cert_store_ctx;
    STACK_OF(SSL_CIPHER) *cipher_list_old = NULL, *cipher_list = NULL;
    SSL_CIPHER *cipher = NULL;
    int depth, verify_old, verify, n;

    if (ssl) {
        ctx = SSL_get_SSL_CTX(ssl);
    }

    /*
     * Support for SSLRequireSSL directive
     */
    if (dc->bSSLRequired && !ssl) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, 
                      "access to %s failed, reason: %s",
                      r->filename, "SSL connection required");

        /* remember forbidden access for strict require option */
        apr_table_setn(r->notes, "ssl-access-forbidden", "1");

        return HTTP_FORBIDDEN;
    }

    /*
     * Check to see if SSL protocol is on
     */
    if (!(sc->enabled || ssl)) {
        return DECLINED;
    }
    /*
     * Support for per-directory reconfigured SSL connection parameters.
     *
     * This is implemented by forcing an SSL renegotiation with the
     * reconfigured parameter suite. But Apache's internal API processing
     * makes our life very hard here, because when internal sub-requests occur
     * we nevertheless should avoid multiple unnecessary SSL handshakes (they
     * require extra network I/O and especially time to perform). 
     * 
     * But the optimization for filtering out the unnecessary handshakes isn't
     * obvious and trivial.  Especially because while Apache is in its
     * sub-request processing the client could force additional handshakes,
     * too. And these take place perhaps without our notice. So the only
     * possibility is to explicitly _ask_ OpenSSL whether the renegotiation
     * has to be performed or not. It has to performed when some parameters
     * which were previously known (by us) are not those we've now
     * reconfigured (as known by OpenSSL) or (in optimized way) at least when
     * the reconfigured parameter suite is stronger (more restrictions) than
     * the currently active one.
     */

    /*
     * Override of SSLCipherSuite
     *
     * We provide two options here:
     *
     * o The paranoid and default approach where we force a renegotiation when
     *   the cipher suite changed in _any_ way (which is straight-forward but
     *   often forces renegotiations too often and is perhaps not what the
     *   user actually wanted).
     *
     * o The optimized and still secure way where we force a renegotiation
     *   only if the currently active cipher is no longer contained in the
     *   reconfigured/new cipher suite. Any other changes are not important
     *   because it's the servers choice to select a cipher from the ones the
     *   client supports. So as long as the current cipher is still in the new
     *   cipher suite we're happy. Because we can assume we would have
     *   selected it again even when other (better) ciphers exists now in the
     *   new cipher suite. This approach is fine because the user explicitly
     *   has to enable this via ``SSLOptions +OptRenegotiate''. So we do no
     *   implicit optimizations.
     */
    if (dc->szCipherSuite) {
        /* remember old state */

        if (dc->nOptions & SSL_OPT_OPTRENEGOTIATE) {
            cipher = SSL_get_current_cipher(ssl);
        }
        else {
            cipher_list_old = (STACK_OF(SSL_CIPHER) *)SSL_get_ciphers(ssl);

            if (cipher_list_old) {
                cipher_list_old = sk_SSL_CIPHER_dup(cipher_list_old);
            }
        }

        /* configure new state */
        if (!modssl_set_cipher_list(ssl, dc->szCipherSuite)) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                         r->server,
                         "Unable to reconfigure (per-directory) "
                         "permitted SSL ciphers");
            ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, r->server);

            if (cipher_list_old) {
                sk_SSL_CIPHER_free(cipher_list_old);
            }

            return HTTP_FORBIDDEN;
        }

        /* determine whether a renegotiation has to be forced */
        cipher_list = (STACK_OF(SSL_CIPHER) *)SSL_get_ciphers(ssl);

        if (dc->nOptions & SSL_OPT_OPTRENEGOTIATE) {
            /* optimized way */
            if ((!cipher && cipher_list) ||
                (cipher && !cipher_list))
            {
                renegotiate = TRUE;
            }
            else if (cipher && cipher_list &&
                     (sk_SSL_CIPHER_find(cipher_list, cipher) < 0))
            {
                renegotiate = TRUE;
            }
        }
        else {
            /* paranoid way */
            if ((!cipher_list_old && cipher_list) ||
                (cipher_list_old && !cipher_list))
            {
                renegotiate = TRUE;
            }
            else if (cipher_list_old && cipher_list) {
                for (n = 0;
                     !renegotiate && (n < sk_SSL_CIPHER_num(cipher_list));
                     n++)
                {
                    SSL_CIPHER *value = sk_SSL_CIPHER_value(cipher_list, n);

                    if (sk_SSL_CIPHER_find(cipher_list_old, value) < 0) {
                        renegotiate = TRUE;
                    }
                }

                for (n = 0;
                     !renegotiate && (n < sk_SSL_CIPHER_num(cipher_list_old));
                     n++)
                {
                    SSL_CIPHER *value = sk_SSL_CIPHER_value(cipher_list_old, n);

                    if (sk_SSL_CIPHER_find(cipher_list, value) < 0) {
                        renegotiate = TRUE;
                    }
                }
            }
        }

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
     * stronger than the currently active verify type. 
     *
     * The order is: none << optional_no_ca << optional << require
     *
     * Additionally the following optimization is possible here: When the
     * currently active verify type is "none" but a client certificate is
     * already known/present, it's enough to manually force a client
     * verification but at least skip the I/O-intensive renegotation
     * handshake.
     */
    if (dc->nVerifyClient != SSL_CVERIFY_UNSET) {
        /* remember old state */
        verify_old = SSL_get_verify_mode(ssl);
        /* configure new state */
        verify = SSL_VERIFY_NONE;

        if (dc->nVerifyClient == SSL_CVERIFY_REQUIRE) {
            verify |= SSL_VERIFY_PEER_STRICT;
        }

        if ((dc->nVerifyClient == SSL_CVERIFY_OPTIONAL) ||
            (dc->nVerifyClient == SSL_CVERIFY_OPTIONAL_NO_CA))
        {
            verify |= SSL_VERIFY_PEER;
        }

        modssl_set_verify(ssl, verify, ssl_callback_SSLVerify);
        SSL_set_verify_result(ssl, X509_V_OK);

        /* determine whether we've to force a renegotiation */
        if (!renegotiate && verify != verify_old) {
            if (((verify_old == SSL_VERIFY_NONE) &&
                 (verify     != SSL_VERIFY_NONE)) ||

                (!(verify_old & SSL_VERIFY_PEER) &&
                  (verify     & SSL_VERIFY_PEER)) ||

                (!(verify_old & SSL_VERIFY_PEER_STRICT) &&
                  (verify     & SSL_VERIFY_PEER_STRICT)))
            {
                renegotiate = TRUE;
                /* optimization */

                if ((dc->nOptions & SSL_OPT_OPTRENEGOTIATE) &&
                    (verify_old == SSL_VERIFY_NONE) &&
                    ((peercert = SSL_get_peer_certificate(ssl)) != NULL))
                {
                    renegotiate_quick = TRUE;
                    X509_free(peercert);
                }

                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                             r->server,
                             "Changed client verification type will force "
                             "%srenegotiation",
                             renegotiate_quick ? "quick " : "");
             }
        }
    }

    /*
     * override SSLCACertificateFile & SSLCACertificatePath
     * This is only enabled if the SSL_set_cert_store() function
     * is available in the ssl library.  the 1.x based mod_ssl
     * used SSL_CTX_set_cert_store which is not thread safe.
     */

#ifdef HAVE_SSL_SET_CERT_STORE
    /*
     * check if per-dir and per-server config field are not the same.
     * if f is defined in per-dir and not defined in per-server
     * or f is defined in both but not the equal ...
     */
#define MODSSL_CFG_NE(f) \
     (dc->f && (!sc->f || (sc->f && strNE(dc->f, sc->f))))

#define MODSSL_CFG_CA(f) \
     (dc->f ? dc->f : sc->f)

    if (MODSSL_CFG_NE(szCACertificateFile) ||
        MODSSL_CFG_NE(szCACertificatePath))
    {
        STACK_OF(X509_NAME) *ca_list;
        const char *ca_file = MODSSL_CFG_CA(szCACertificateFile);
        const char *ca_path = MODSSL_CFG_CA(szCACertificatePath);

        cert_store = X509_STORE_new();

        if (!X509_STORE_load_locations(cert_store, ca_file, ca_path)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                         "Unable to reconfigure verify locations "
                         "for client authentication");
            ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, r->server);

            X509_STORE_free(cert_store);

            return HTTP_FORBIDDEN;
        }

        /* SSL_free will free cert_store */
        SSL_set_cert_store(ssl, cert_store);

        if (!(ca_list = ssl_init_FindCAList(r->server, r->pool,
                                            ca_file, ca_path)))
        {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                         "Unable to determine list of available "
                         "CA certificates for client authentication");

            return HTTP_FORBIDDEN;
        }

        SSL_set_client_CA_list(ssl, ca_list);
        renegotiate = TRUE;

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "Changed client verification locations will force "
                     "renegotiation");
    }
#endif /* HAVE_SSL_SET_CERT_STORE */

    /* 
     * SSL renegotiations in conjunction with HTTP
     * requests using the POST method are not supported.
     *
     * Background:
     *
     * 1. When the client sends a HTTP/HTTPS request, Apache's core code
     * reads only the request line ("METHOD /path HTTP/x.y") and the
     * attached MIME headers ("Foo: bar") up to the terminating line ("CR
     * LF"). An attached request body (for instance the data of a POST
     * method) is _NOT_ read. Instead it is read by mod_cgi's content
     * handler and directly passed to the CGI script.
     *
     * 2. mod_ssl supports per-directory re-configuration of SSL parameters.
     * This is implemented by performing an SSL renegotiation of the
     * re-configured parameters after the request is read, but before the
     * response is sent. In more detail: the renegotiation happens after the
     * request line and MIME headers were read, but _before_ the attached
     * request body is read. The reason simply is that in the HTTP protocol
     * usually there is no acknowledgment step between the headers and the
     * body (there is the 100-continue feature and the chunking facility
     * only), so Apache has no API hook for this step.
     *
     * 3. the problem now occurs when the client sends a POST request for
     * URL /foo via HTTPS the server and the server has SSL parameters
     * re-configured on a per-URL basis for /foo. Then mod_ssl has to
     * perform an SSL renegotiation after the request was read and before
     * the response is sent. But the problem is the pending POST body data
     * in the receive buffer of SSL (which Apache still has not read - it's
     * pending until mod_cgi sucks it in). When mod_ssl now tries to perform
     * the renegotiation the pending data leads to an I/O error.
     *
     * Solution Idea:
     *
     * There are only two solutions: Either to simply state that POST
     * requests to URLs with SSL re-configurations are not allowed, or to
     * renegotiate really after the _complete_ request (i.e. including
     * the POST body) was read. Obviously the latter would be preferred,
     * but it cannot be done easily inside Apache, because as already
     * mentioned, there is no API step between the body reading and the body
     * processing. And even when we mod_ssl would hook directly into the
     * loop of mod_cgi, we wouldn't solve the problem for other handlers, of
     * course. So the only general solution is to suck in the pending data
     * of the request body from the OpenSSL BIO into the Apache BUFF. Then
     * the renegotiation can be done and after this step Apache can proceed
     * processing the request as before.
     *
     * Solution Implementation:
     *
     * We cannot simply suck in the data via an SSL_read-based loop because of
     * HTTP chunking. Instead we _have_ to use the Apache API for this step which
     * is aware of HTTP chunking. So the trick is to suck in the pending request
     * data via the Apache API (which uses Apache's BUFF code and in the
     * background mod_ssl's I/O glue code) and re-inject it later into the Apache
     * BUFF code again. This way the data flows twice through the Apache BUFF, of
     * course. But this way the solution doesn't depend on any Apache specifics
     * and is fully transparent to Apache modules.
     *
     * !! BUT ALL THIS IS STILL NOT RE-IMPLEMENTED FOR APACHE 2.0 !!
     */
    if (renegotiate && !renegotiate_quick && (r->method_number == M_POST)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "SSL Re-negotiation in conjunction "
                     "with POST method not supported!\n"
                     "hint: try SSLOptions +OptRenegotiate");

        return HTTP_METHOD_NOT_ALLOWED;
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
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                     "Requesting connection re-negotiation");

        if (renegotiate_quick) {
            STACK_OF(X509) *cert_stack;

            /* perform just a manual re-verification of the peer */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "Performing quick renegotiation: "
                         "just re-verifying the peer");

            cert_stack = (STACK_OF(X509) *)SSL_get_peer_cert_chain(ssl);

            cert = SSL_get_peer_certificate(ssl);

            if (!cert_stack && cert) {
                /* client cert is in the session cache, but there is
                 * no chain, since ssl3_get_client_certificate()
                 * sk_X509_shift-ed the peer cert out of the chain.
                 * we put it back here for the purpose of quick_renegotiation.
                 */
                cert_stack = sk_new_null();
                sk_X509_push(cert_stack, MODSSL_PCHAR_CAST cert);
            }

            if (!cert_stack || (sk_X509_num(cert_stack) == 0)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "Cannot find peer certificate chain");

                return HTTP_FORBIDDEN;
            }

            if (!(cert_store ||
                  (cert_store = SSL_CTX_get_cert_store(ctx))))
            {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "Cannot find certificate storage");

                return HTTP_FORBIDDEN;
            }

            if (!cert) {
                cert = sk_X509_value(cert_stack, 0);
            }

            X509_STORE_CTX_init(&cert_store_ctx, cert_store, cert, cert_stack);
            depth = SSL_get_verify_depth(ssl);

            if (depth >= 0) {
                X509_STORE_CTX_set_depth(&cert_store_ctx, depth);
            }

            X509_STORE_CTX_set_ex_data(&cert_store_ctx,
                                       SSL_get_ex_data_X509_STORE_CTX_idx(),
                                       (char *)ssl);

            if (!modssl_X509_verify_cert(&cert_store_ctx)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "Re-negotiation verification step failed");
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, r->server);
            }

            SSL_set_verify_result(ssl, cert_store_ctx.error);
            X509_STORE_CTX_cleanup(&cert_store_ctx);

            if (cert_stack != SSL_get_peer_cert_chain(ssl)) {
                /* we created this ourselves, so free it */
                sk_X509_pop_free(cert_stack, X509_free);
            }
        }
        else {
            request_rec *id = r->main ? r->main : r;

            /* do a full renegotiation */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "Performing full renegotiation: "
                         "complete handshake protocol");

            SSL_set_session_id_context(ssl,
                                       (unsigned char *)&id,
                                       sizeof(id));

            SSL_renegotiate(ssl);
            SSL_do_handshake(ssl);

            if (SSL_get_state(ssl) != SSL_ST_OK) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "Re-negotiation request failed");

                r->connection->aborted = 1;
                return HTTP_FORBIDDEN;
            }

            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                         "Awaiting re-negotiation handshake");

            SSL_set_state(ssl, SSL_ST_ACCEPT);
            SSL_do_handshake(ssl);

            if (SSL_get_state(ssl) != SSL_ST_OK) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "Re-negotiation handshake failed: "
                        "Not accepted by client!?");

                r->connection->aborted = 1;
                return HTTP_FORBIDDEN;
            }
        }

        /*
         * Remember the peer certificate's DN
         */
        if ((cert = SSL_get_peer_certificate(ssl))) {
            if (sslconn->client_cert) {
                X509_free(sslconn->client_cert);
            }
            sslconn->client_cert = cert;
            sslconn->client_dn = NULL;
        }

        /*
         * Finally check for acceptable renegotiation results
         */
        if (dc->nVerifyClient != SSL_CVERIFY_NONE) {
            BOOL do_verify = (dc->nVerifyClient == SSL_CVERIFY_REQUIRE);

            if (do_verify && (SSL_get_verify_result(ssl) != X509_V_OK)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "Re-negotiation handshake failed: "
                             "Client verification failed");

                return HTTP_FORBIDDEN;
            }

            if (do_verify) {
                if ((peercert = SSL_get_peer_certificate(ssl)) == NULL) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                                 "Re-negotiation handshake failed: "
                                 "Client certificate missing");

                    return HTTP_FORBIDDEN;
                }

                X509_free(peercert);
            }
        }
        
        /*
         * Also check that SSLCipherSuite has been enforced as expected.
         */
        if (cipher_list) {
            cipher = SSL_get_current_cipher(ssl);
            if (sk_SSL_CIPHER_find(cipher_list, cipher) < 0) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                             "SSL cipher suite not renegotiated: "
                             "access to %s denied using cipher %s",
                              r->filename,
                              SSL_CIPHER_get_name(cipher));
                return HTTP_FORBIDDEN;
            }
        }
    }

    /*
     * Check SSLRequire boolean expressions
     */
    requires = dc->aRequirement;
    ssl_requires = (ssl_require_t *)requires->elts;

    for (i = 0; i < requires->nelts; i++) {
        ssl_require_t *req = &ssl_requires[i];
        ok = ssl_expr_exec(r, req->mpExpr);

        if (ok < 0) {
            cp = apr_psprintf(r->pool,
                              "Failed to execute "
                              "SSL requirement expression: %s",
                              ssl_expr_get_error());

            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, 
                          "access to %s failed, reason: %s",
                          r->filename, cp);

            /* remember forbidden access for strict require option */
            apr_table_setn(r->notes, "ssl-access-forbidden", "1");

            return HTTP_FORBIDDEN;
        }

        if (ok != 1) {
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                         "Access to %s denied for %s "
                         "(requirement expression not fulfilled)",
                         r->filename, r->connection->remote_ip);

            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                         "Failed expression: %s", req->cpExpr);

            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, 
                          "access to %s failed, reason: %s",
                          r->filename,
                          "SSL requirement expression not fulfilled "
                          "(see SSL logfile for more details)");

            /* remember forbidden access for strict require option */
            apr_table_setn(r->notes, "ssl-access-forbidden", "1");

            return HTTP_FORBIDDEN;
        }
    }

    /*
     * Else access is granted from our point of view (except vendor
     * handlers override). But we have to return DECLINED here instead
     * of OK, because mod_auth and other modules still might want to
     * deny access.
     */

    return DECLINED;
}