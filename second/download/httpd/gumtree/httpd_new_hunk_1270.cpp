                sk_X509_pop_free(cert_stack, X509_free);
            }
        }
        else {
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
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "insecure SSL re-negotiation required, but "
                              "a pipelined request is present; keepalive "
                              "disabled");
                r->connection->keepalive = AP_CONN_CLOSE;
            }

            /* Perform a full renegotiation. */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "Performing full renegotiation: complete handshake "
                          "protocol (%s support secure renegotiation)",
#if defined(SSL_get_secure_renegotiation_support)
                          SSL_get_secure_renegotiation_support(ssl) ? 
                          "client does" : "client does not"
#else
                          "server does not"
#endif
                );

            SSL_set_session_id_context(ssl,
                                       (unsigned char *)&id,
                                       sizeof(id));

            /* Toggle the renegotiation state to allow the new
             * handshake to proceed. */
            sslconn->reneg_state = RENEG_ALLOW;
            
            SSL_renegotiate(ssl);
            SSL_do_handshake(ssl);

            if (SSL_get_state(ssl) != SSL_ST_OK) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Re-negotiation request failed");
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, r->server);

                r->connection->aborted = 1;
                return HTTP_FORBIDDEN;
            }

            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
