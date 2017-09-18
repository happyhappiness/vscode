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
