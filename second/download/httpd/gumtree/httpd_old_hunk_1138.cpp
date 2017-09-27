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
