#define modssl_set_cert_info(info, cert, pkey) \
    *cert = info->x509; \
    X509_reference_inc(*cert); \
    *pkey = info->x_pkey->dec_pkey; \
    EVP_PKEY_reference_inc(*pkey)

int ssl_callback_proxy_cert(SSL *ssl, MODSSL_CLIENT_CERT_CB_ARG_TYPE **x509, EVP_PKEY **pkey)
{
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
    server_rec *s = c->base_server;
    SSLSrvConfigRec *sc = mySrvConfig(s);
    X509_NAME *ca_name, *issuer;
    X509_INFO *info;
    STACK_OF(X509_NAME) *ca_list;
    STACK_OF(X509_INFO) *certs = sc->proxy->pkp->certs;
    int i, j;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 SSLPROXY_CERT_CB_LOG_FMT "entered",
                 sc->vhost_id);

    if (!certs || (sk_X509_INFO_num(certs) <= 0)) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
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

        modssl_proxy_info_log(s, info, "no acceptable CA list");

        modssl_set_cert_info(info, x509, pkey);

        return TRUE;
    }

    for (i = 0; i < sk_X509_NAME_num(ca_list); i++) {
        ca_name = sk_X509_NAME_value(ca_list, i);

        for (j = 0; j < sk_X509_INFO_num(certs); j++) {
            info = sk_X509_INFO_value(certs, j);
