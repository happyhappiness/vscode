        if (!inf->x509 || !inf->x_pkey || !inf->x_pkey->dec_pkey ||
            inf->enc_data) {
            sk_X509_INFO_free(sk);
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, s, APLOGNO(02252)
                         "incomplete client cert configured for SSL proxy "
                         "(missing or encrypted private key?)");
            return ssl_die(s);
        }
        
        if (X509_check_private_key(inf->x509, inf->x_pkey->dec_pkey) != 1) {
            ssl_log_xerror(SSLLOG_MARK, APLOG_STARTUP, 0, ptemp, s, inf->x509,
                           APLOGNO(02326) "proxy client certificate and "
                           "private key do not match");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
            return ssl_die(s);
        }
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02207)
                 "loaded %d client certs for SSL proxy",
                 ncerts);
    pkp->certs = sk;


    if (!pkp->ca_cert_file || !store) {
        return APR_SUCCESS;
    }

    /* If SSLProxyMachineCertificateChainFile is configured, load all
     * the CA certs and have OpenSSL attempt to construct a full chain
     * from each configured end-entity cert up to a root.  This will
     * allow selection of the correct cert given a list of root CA
