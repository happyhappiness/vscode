int ssl_callback_proxy_cert(SSL *ssl, X509 **x509, EVP_PKEY **pkey)
{
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
    server_rec *s = mySrvFromConn(c);
    SSLSrvConfigRec *sc = mySrvConfig(s);
    X509_NAME *ca_name, *issuer, *ca_issuer;
    X509_INFO *info;
    X509 *ca_cert;
    STACK_OF(X509_NAME) *ca_list;
    STACK_OF(X509_INFO) *certs = sc->proxy->pkp->certs;
    STACK_OF(X509) *ca_certs;
    STACK_OF(X509) **ca_cert_chains;
    int i, j, k;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02267)
                 SSLPROXY_CERT_CB_LOG_FMT "entered",
                 sc->vhost_id);

    if (!certs || (sk_X509_INFO_num(certs) <= 0)) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(02268)
                     SSLPROXY_CERT_CB_LOG_FMT
                     "downstream server wanted client certificate "
                     "but none are configured", sc->vhost_id);
        return FALSE;
    }

    ca_list = SSL_get_client_CA_list(ssl);

    if (!ca_list || (sk_X509_NAME_num(ca_list) <= 0)) {
        /*
         * downstream server didn't send us a list of acceptable CA certs,
         * so we send the first client cert in the list.
         */
        info = sk_X509_INFO_value(certs, 0);

        modssl_proxy_info_log(c, info, APLOGNO(02278) "no acceptable CA list");

        modssl_set_cert_info(info, x509, pkey);

        return TRUE;
    }

    ca_cert_chains = sc->proxy->pkp->ca_certs;
    for (i = 0; i < sk_X509_NAME_num(ca_list); i++) {
        ca_name = sk_X509_NAME_value(ca_list, i);

        for (j = 0; j < sk_X509_INFO_num(certs); j++) {
            info = sk_X509_INFO_value(certs, j);
            issuer = X509_get_issuer_name(info->x509);

            /* Search certs (by issuer name) one by one*/
            if (X509_NAME_cmp(issuer, ca_name) == 0) {
                modssl_proxy_info_log(c, info, APLOGNO(02279)
                                      "found acceptable cert");

                modssl_set_cert_info(info, x509, pkey);

                return TRUE;
            }

            if (ca_cert_chains) {
                /*
                 * Failed to find direct issuer - search intermediates
                 * (by issuer name), if provided.
                 */
                ca_certs = ca_cert_chains[j];
                for (k = 0; k < sk_X509_num(ca_certs); k++) {
                    ca_cert = sk_X509_value(ca_certs, k);
                    ca_issuer = X509_get_issuer_name(ca_cert);

                    if(X509_NAME_cmp(ca_issuer, ca_name) == 0 ) {
                        modssl_proxy_info_log(c, info, APLOGNO(02280)
                                              "found acceptable cert by intermediate CA");

                        modssl_set_cert_info(info, x509, pkey);

                        return TRUE;
                    }
                } /* end loop through chained certs */
            }
        } /* end loop through available certs */
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02269)
                 SSLPROXY_CERT_CB_LOG_FMT
                 "no client certificate found!?", sc->vhost_id);

    return FALSE;
}