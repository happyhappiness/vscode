int ssl_hook_Access(request_rec *r)
{
    SSLDirConfigRec *dc         = myDirConfig(r);
    SSLSrvConfigRec *sc         = mySrvConfig(r->server);
    SSLConnRec *sslconn         = myConnConfig(r->connection);
    SSL *ssl                    = sslconn ? sslconn->ssl : NULL;
    server_rec *handshakeserver = sslconn ? sslconn->server : NULL;
    SSL_CTX *ctx = NULL;
    apr_array_header_t *requires;
    ssl_require_t *ssl_requires;
    int ok, i;
    BOOL renegotiate = FALSE, renegotiate_quick = FALSE;
    X509 *cert;
    X509 *peercert;
    X509_STORE *cert_store = NULL;
    X509_STORE_CTX cert_store_ctx;
    STACK_OF(SSL_CIPHER) *cipher_list_old = NULL, *cipher_list = NULL;
    const SSL_CIPHER *cipher = NULL;
    int depth, verify_old, verify, n;

    if (ssl) {
        ctx = SSL_get_SSL_CTX(ssl);
    }

    /*
     * Support for SSLRequireSSL directive
     */
    if (dc->bSSLRequired && !ssl) {
        if (sc->enabled == SSL_ENABLED_OPTIONAL) {
            /* This vhost was configured for optional SSL, just tell the
             * client that we need to upgrade.
             */
            apr_table_setn(r->err_headers_out, "Upgrade", "TLS/1.0, HTTP/1.1");
            apr_table_setn(r->err_headers_out, "Connection", "Upgrade");

            return HTTP_UPGRADE_REQUIRED;
        }

        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02219)
                      "access to %s failed, reason: %s",
                      r->filename, "SSL connection required");

        /* remember forbidden access for strict require option */
        apr_table_setn(r->notes, "ssl-access-forbidden", "1");

        return HTTP_FORBIDDEN;
    }

    /*
     * Check to see whether SSL is in use; if it's not, then no
     * further access control checks are relevant.  (the test for
     * sc->enabled is probably strictly unnecessary)
     */
    if (sc->enabled == SSL_ENABLED_FALSE || !ssl) {
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
    if (dc->szCipherSuite || (r->server != handshakeserver)) {
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
        if ((dc->szCipherSuite || sc->server->auth.cipher_suite) &&
            !SSL_set_cipher_list(ssl, dc->szCipherSuite ?
                                      dc->szCipherSuite :
                                      sc->server->auth.cipher_suite)) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02253)
                          "Unable to reconfigure (per-directory) "
                          "permitted SSL ciphers");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, r->server);

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

        if (renegotiate) {
#ifdef SSL_OP_CIPHER_SERVER_PREFERENCE
            if (sc->cipher_server_pref == TRUE) {
                SSL_set_options(ssl, SSL_OP_CIPHER_SERVER_PREFERENCE);
            }
#endif
            /* tracing */
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
     *
     * Additionally the following optimization is possible here: When the
     * currently active verify type is "none" but a client certificate is
     * already known/present, it's enough to manually force a client
     * verification but at least skip the I/O-intensive renegotiation
     * handshake.
     */
    if ((dc->nVerifyClient != SSL_CVERIFY_UNSET) ||
        (sc->server->auth.verify_mode != SSL_CVERIFY_UNSET)) {
        /* remember old state */
        verify_old = SSL_get_verify_mode(ssl);
        /* configure new state */
        verify = SSL_VERIFY_NONE;

        if ((dc->nVerifyClient == SSL_CVERIFY_REQUIRE) ||
            (sc->server->auth.verify_mode == SSL_CVERIFY_REQUIRE)) {
            verify |= SSL_VERIFY_PEER_STRICT;
        }

        if ((dc->nVerifyClient == SSL_CVERIFY_OPTIONAL) ||
            (dc->nVerifyClient == SSL_CVERIFY_OPTIONAL_NO_CA) ||
            (sc->server->auth.verify_mode == SSL_CVERIFY_OPTIONAL) ||
            (sc->server->auth.verify_mode == SSL_CVERIFY_OPTIONAL_NO_CA))
        {
            verify |= SSL_VERIFY_PEER;
        }

        SSL_set_verify(ssl, verify, ssl_callback_SSLVerify);
        SSL_set_verify_result(ssl, X509_V_OK);

        /* determine whether we've to force a renegotiation */
        if (!renegotiate && verify != verify_old) {
            if (((verify_old == SSL_VERIFY_NONE) &&
                 (verify     != SSL_VERIFY_NONE)) ||

                (!(verify_old & SSL_VERIFY_PEER) &&
                  (verify     & SSL_VERIFY_PEER)) ||

                (!(verify_old & SSL_VERIFY_FAIL_IF_NO_PEER_CERT) &&
                  (verify     & SSL_VERIFY_FAIL_IF_NO_PEER_CERT)))
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

                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02255)
                              "Changed client verification type will force "
                              "%srenegotiation",
                              renegotiate_quick ? "quick " : "");
             }
        }
        /* If we're handling a request for a vhost other than the default one,
         * then we need to make sure that client authentication is properly
         * enforced. For clients supplying an SNI extension, the peer
         * certificate verification has happened in the handshake already
         * (and r->server == handshakeserver). For non-SNI requests,
         * an additional check is needed here. If client authentication
         * is configured as mandatory, then we can only proceed if the
         * CA list doesn't have to be changed (OpenSSL doesn't provide
         * an option to change the list for an existing session).
         */
        if ((r->server != handshakeserver)
            && renegotiate
            && ((verify & SSL_VERIFY_PEER) ||
                (verify & SSL_VERIFY_FAIL_IF_NO_PEER_CERT))) {
            SSLSrvConfigRec *hssc = mySrvConfig(handshakeserver);

#define MODSSL_CFG_CA_NE(f, sc1, sc2) \
            (sc1->server->auth.f && \
             (!sc2->server->auth.f || \
              strNE(sc1->server->auth.f, sc2->server->auth.f)))

            if (MODSSL_CFG_CA_NE(ca_cert_file, sc, hssc) ||
                MODSSL_CFG_CA_NE(ca_cert_path, sc, hssc)) {
                if (verify & SSL_VERIFY_FAIL_IF_NO_PEER_CERT) {
                    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02256)
                         "Non-default virtual host with SSLVerify set to "
                         "'require' and VirtualHost-specific CA certificate "
                         "list is only available to clients with TLS server "
                         "name indication (SNI) support");
                    SSL_set_verify(ssl, verify_old, NULL);
                    return HTTP_FORBIDDEN;
                } else
                    /* let it pass, possibly with an "incorrect" peer cert,
                     * so make sure the SSL_CLIENT_VERIFY environment variable
                     * will indicate partial success only, later on.
                     */
                    sslconn->verify_info = "GENEROUS";
            }
        }
    }

    /* If a renegotiation is now required for this location, and the
     * request includes a message body (and the client has not
     * requested a "100 Continue" response), then the client will be
     * streaming the request body over the wire already.  In that
     * case, it is not possible to stop and perform a new SSL
     * handshake immediately; once the SSL library moves to the
     * "accept" state, it will reject the SSL packets which the client
     * is sending for the request body.
     *
     * To allow authentication to complete in this auth hook, the
     * solution used here is to fill a (bounded) buffer with the
     * request body, and then to reinject that request body later.
     */
    if (renegotiate && !renegotiate_quick
        && (apr_table_get(r->headers_in, "transfer-encoding")
            || (apr_table_get(r->headers_in, "content-length")
                && strcmp(apr_table_get(r->headers_in, "content-length"), "0")))
        && !r->expecting_100) {
        int rv;
        apr_size_t rsize;

        rsize = dc->nRenegBufferSize == UNSET ? DEFAULT_RENEG_BUFFER_SIZE :
                                                dc->nRenegBufferSize;
        if (rsize > 0) {
            /* Fill the I/O buffer with the request body if possible. */
            rv = ssl_io_buffer_fill(r, rsize);
        }
        else {
            /* If the reneg buffer size is set to zero, just fail. */
            rv = HTTP_REQUEST_ENTITY_TOO_LARGE;
        }

        if (rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02257)
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
         * Now we force the SSL renegotiation by sending the Hello Request
         * message to the client. Here we have to do a workaround: Actually
         * OpenSSL returns immediately after sending the Hello Request (the
         * intent AFAIK is because the SSL/TLS protocol says it's not a must
         * that the client replies to a Hello Request). But because we insist
         * on a reply (anything else is an error for us) we have to go to the
         * ACCEPT state manually. Using SSL_set_accept_state() doesn't work
         * here because it resets too much of the connection.  So we set the
         * state explicitly and continue the handshake manually.
         */
        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02221)
                      "Requesting connection re-negotiation");

        if (renegotiate_quick) {
            STACK_OF(X509) *cert_stack;

            /* perform just a manual re-verification of the peer */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02258)
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
                cert_stack = sk_X509_new_null();
                sk_X509_push(cert_stack, cert);
            }

            if (!cert_stack || (sk_X509_num(cert_stack) == 0)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02222)
                              "Cannot find peer certificate chain");

                return HTTP_FORBIDDEN;
            }

            if (!(cert_store ||
                  (cert_store = SSL_CTX_get_cert_store(ctx))))
            {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02223)
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

            if (!X509_verify_cert(&cert_store_ctx)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02224)
                              "Re-negotiation verification step failed");
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, r->server);
            }

            SSL_set_verify_result(ssl, cert_store_ctx.error);
            X509_STORE_CTX_cleanup(&cert_store_ctx);

            if (cert_stack != SSL_get_peer_cert_chain(ssl)) {
                /* we created this ourselves, so free it */
                sk_X509_pop_free(cert_stack, X509_free);
            }
        }
        else {
            const char *reneg_support;
            request_rec *id = r->main ? r->main : r;

            /* Additional mitigation for CVE-2009-3555: At this point,
             * before renegotiating, an (entire) request has been read
             * from the connection.  An attacker may have sent further
             * data to "prefix" any subsequent request by the victim's
             * client after the renegotiation; this data may already
             * have been read and buffered.  Forcing a connection
             * closure after the response ensures such data will be
             * discarded.  Legimately pipelined HTTP requests will be
             * retried anyway with this approach. */
            if (has_buffered_data(r)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02259)
                              "insecure SSL re-negotiation required, but "
                              "a pipelined request is present; keepalive "
                              "disabled");
                r->connection->keepalive = AP_CONN_CLOSE;
            }

#if defined(SSL_get_secure_renegotiation_support)
            reneg_support = SSL_get_secure_renegotiation_support(ssl) ?
                            "client does" : "client does not";
#else
            reneg_support = "server does not";
#endif
            /* Perform a full renegotiation. */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02260)
                          "Performing full renegotiation: complete handshake "
                          "protocol (%s support secure renegotiation)",
                          reneg_support);

            SSL_set_session_id_context(ssl,
                                       (unsigned char *)&id,
                                       sizeof(id));

            /* Toggle the renegotiation state to allow the new
             * handshake to proceed. */
            sslconn->reneg_state = RENEG_ALLOW;

            SSL_renegotiate(ssl);
            SSL_do_handshake(ssl);

            if (SSL_get_state(ssl) != SSL_ST_OK) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02225)
                              "Re-negotiation request failed");
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, r->server);

                r->connection->keepalive = AP_CONN_CLOSE;
                return HTTP_FORBIDDEN;
            }

            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02226)
                          "Awaiting re-negotiation handshake");

            /* XXX: Should replace setting state with SSL_renegotiate(ssl);
             * However, this causes failures in perl-framework currently,
             * perhaps pre-test if we have already negotiated?
             */
#ifdef OPENSSL_NO_SSL_INTERN
            SSL_set_state(ssl, SSL_ST_ACCEPT);
#else
            ssl->state = SSL_ST_ACCEPT;
#endif
            SSL_do_handshake(ssl);

            sslconn->reneg_state = RENEG_REJECT;

            if (SSL_get_state(ssl) != SSL_ST_OK) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02261)
                              "Re-negotiation handshake failed: "
                              "Not accepted by client!?");

                r->connection->keepalive = AP_CONN_CLOSE;
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
        if ((dc->nVerifyClient != SSL_CVERIFY_NONE) ||
            (sc->server->auth.verify_mode != SSL_CVERIFY_NONE)) {
            BOOL do_verify = ((dc->nVerifyClient == SSL_CVERIFY_REQUIRE) ||
                              (sc->server->auth.verify_mode == SSL_CVERIFY_REQUIRE));

            if (do_verify && (SSL_get_verify_result(ssl) != X509_V_OK)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02262)
                              "Re-negotiation handshake failed: "
                              "Client verification failed");

                return HTTP_FORBIDDEN;
            }

            if (do_verify) {
                if ((peercert = SSL_get_peer_certificate(ssl)) == NULL) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02263)
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
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02264)
                             "SSL cipher suite not renegotiated: "
                             "access to %s denied using cipher %s",
                              r->filename,
                              SSL_CIPHER_get_name(cipher));
                return HTTP_FORBIDDEN;
            }
        }
    }

    /* If we're trying to have the user name set from a client
     * certificate then we need to set it here. This should be safe as
     * the user name probably isn't important from an auth checking point
     * of view as the certificate supplied acts in that capacity.
     * However, if FakeAuth is being used then this isn't the case so
     * we need to postpone setting the username until later.
     */
    if ((dc->nOptions & SSL_OPT_FAKEBASICAUTH) == 0 && dc->szUserName) {
 