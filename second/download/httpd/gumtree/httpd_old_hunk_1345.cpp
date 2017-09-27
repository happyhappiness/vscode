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
