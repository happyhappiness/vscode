                    (verify_old == SSL_VERIFY_NONE) &&
                    SSL_get_peer_certificate(ssl))
                {
                    renegotiate_quick = TRUE;
                }

                ssl_log(r->server, SSL_LOG_TRACE,
                        "Changed client verification type "
                        "will force %srenegotiation",
                        renegotiate_quick ? "quick " : "");
             }
        }
    }

    /*
     * override SSLCACertificateFile & SSLCACertificatePath
