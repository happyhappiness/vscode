    /*
     * And finally signal OpenSSL the (perhaps changed) state
     */
    return ok;
}

#define SSLPROXY_CERT_CB_LOG_FMT \
   "Proxy client certificate callback: (%s) "

static void modssl_proxy_info_log(conn_rec *c,
                                  X509_INFO *info,
                                  const char *msg)
{
    ssl_log_cxerror(SSLLOG_MARK, APLOG_DEBUG, 0, c, info->x509, APLOGNO(02277)
                    SSLPROXY_CERT_CB_LOG_FMT "%s, sending",
                    (mySrvConfigFromConn(c))->vhost_id, msg);
}

/*
 * caller will decrement the cert and key reference
 * so we need to increment here to prevent them from
 * being freed.
 */
#define modssl_set_cert_info(info, cert, pkey) \
    *cert = info->x509; \
    CRYPTO_add(&(*cert)->references, +1, CRYPTO_LOCK_X509); \
    *pkey = info->x_pkey->dec_pkey; \
    CRYPTO_add(&(*pkey)->references, +1, CRYPTO_LOCK_X509_PKEY)

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

