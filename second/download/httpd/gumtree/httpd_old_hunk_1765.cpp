                     */
                    sslconn->verify_info = "GENEROUS";
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
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
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

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "Changed client verification locations will force "
                      "renegotiation");
    }
#endif /* HAVE_SSL_SET_CERT_STORE */

    /* If a renegotiation is now required for this location, and the
     * request includes a message body (and the client has not
     * requested a "100 Continue" response), then the client will be
     * streaming the request body over the wire already.  In that
     * case, it is not possible to stop and perform a new SSL
     * handshake immediately; once the SSL library moves to the
