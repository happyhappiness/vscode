                }

                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02255)
                              "Changed client verification type will force "
                              "%srenegotiation",
                              renegotiate_quick ? "quick " : "");
            }
            else if (verify != SSL_VERIFY_NONE) {
                /*
                 * override of SSLVerifyDepth
                 *
                 * The depth checks are handled by us manually inside the
                 * verify callback function and not by OpenSSL internally
                 * (and our function is aware of both the per-server and
                 * per-directory contexts). So we cannot ask OpenSSL about
                 * the currently verify depth. Instead we remember it in our
                 * SSLConnRec attached to the SSL* of OpenSSL.  We've to force
                 * the renegotiation if the reconfigured/new verify depth is
                 * less than the currently active/remembered verify depth
                 * (because this means more restriction on the certificate
                 * chain).
                 */
                n = (sslconn->verify_depth != UNSET)
                    ? sslconn->verify_depth
                    : hssc->server->auth.verify_depth;
                /* determine the new depth */
                sslconn->verify_depth = (dc->nVerifyDepth != UNSET)
                                        ? dc->nVerifyDepth
                                        : sc->server->auth.verify_depth;
                if (sslconn->verify_depth < n) {
                    renegotiate = TRUE;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02254)
                                  "Reduced client verification depth will "
                                  "force renegotiation");
                }
            }
        }
        /* If we're handling a request for a vhost other than the default one,
         * then we need to make sure that client authentication is properly
         * enforced. For clients supplying an SNI extension, the peer
         * certificate verification has happened in the handshake already
         * (and r->server == handshakeserver). For non-SNI requests,
