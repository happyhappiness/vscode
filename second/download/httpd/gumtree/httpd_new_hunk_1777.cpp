
int ssl_callback_proxy_cert(SSL *ssl, MODSSL_CLIENT_CERT_CB_ARG_TYPE **x509, EVP_PKEY **pkey)
{
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
    server_rec *s = mySrvFromConn(c);
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
