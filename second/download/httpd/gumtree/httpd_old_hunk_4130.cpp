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
