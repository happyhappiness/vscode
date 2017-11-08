void modssl_var_extract_san_entries(apr_table_t *t, SSL *ssl, apr_pool_t *p)
{
    X509 *xs;
    apr_array_header_t *entries;

    /* subjectAltName entries of the server certificate */
    xs = SSL_get_certificate(ssl);
    if (xs) {
        if (SSL_X509_getSAN(p, xs, GEN_EMAIL, -1, &entries)) {
            extract_san_array(t, "SSL_SERVER_SAN_Email", entries, p);
        }
        if (SSL_X509_getSAN(p, xs, GEN_DNS, -1, &entries)) {
            extract_san_array(t, "SSL_SERVER_SAN_DNS", entries, p);
        }
        /* no need to free xs (refcount does not increase) */
    }

    /* subjectAltName entries of the client certificate */
    xs = SSL_get_peer_certificate(ssl);
    if (xs) {
        if (SSL_X509_getSAN(p, xs, GEN_EMAIL, -1, &entries)) {
            extract_san_array(t, "SSL_CLIENT_SAN_Email", entries, p);
        }
        if (SSL_X509_getSAN(p, xs, GEN_DNS, -1, &entries)) {
            extract_san_array(t, "SSL_CLIENT_SAN_DNS", entries, p);
        }
        X509_free(xs);
    }
}