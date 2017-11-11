static char *ssl_var_lookup_ssl_cert_verify(apr_pool_t *p, conn_rec *c)
{
    SSLConnRec *sslconn = myConnConfig(c);
    char *result;
    long vrc;
    const char *verr;
    const char *vinfo;
    SSL *ssl;
    X509 *xs;

    result = NULL;
    ssl   = sslconn->ssl;
    verr  = sslconn->verify_error;
    vinfo = sslconn->verify_info;
    vrc   = SSL_get_verify_result(ssl);
    xs    = SSL_get_peer_certificate(ssl);

    if (vrc == X509_V_OK && verr == NULL && xs == NULL)
        /* no client verification done at all */
        result = "NONE";
    else if (vrc == X509_V_OK && verr == NULL && vinfo == NULL && xs != NULL)
        /* client verification done successful */
        result = "SUCCESS";
    else if (vrc == X509_V_OK && vinfo != NULL && strEQ(vinfo, "GENEROUS"))
        /* client verification done in generous way */
        result = "GENEROUS";
    else
        /* client verification failed */
        result = apr_psprintf(p, "FAILED:%s", verr);

    if (xs)
        X509_free(xs);
    return result;
}