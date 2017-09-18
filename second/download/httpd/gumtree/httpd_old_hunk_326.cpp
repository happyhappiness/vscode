        const char *ca_file = MODSSL_CFG_CA(szCACertificateFile);
        const char *ca_path = MODSSL_CFG_CA(szCACertificatePath);

        cert_store = X509_STORE_new();

        if (!X509_STORE_load_locations(cert_store, ca_file, ca_path)) {
            ssl_log(r->server, SSL_LOG_ERROR|SSL_ADD_SSLERR,
                    "Unable to reconfigure verify locations "
                    "for client authentication");

            X509_STORE_free(cert_store);

            return HTTP_FORBIDDEN;
        }

        /* SSL_free will free cert_store */
        SSL_set_cert_store(ssl, cert_store);

        if (!(ca_list = ssl_init_FindCAList(r->server, r->pool,
                                            ca_file, ca_path)))
        {
            ssl_log(r->server, SSL_LOG_ERROR,
                    "Unable to determine list of available "
                    "CA certificates for client authentication");

            return HTTP_FORBIDDEN;
        }

        SSL_set_client_CA_list(ssl, ca_list);
        renegotiate = TRUE;

        ssl_log(r->server, SSL_LOG_TRACE,
                "Changed client verification locations "
                "will force renegotiation");
    }
#endif /* HAVE_SSL_SET_CERT_STORE */

    /* 
     * SSL renegotiations in conjunction with HTTP
     * requests using the POST method are not supported.
