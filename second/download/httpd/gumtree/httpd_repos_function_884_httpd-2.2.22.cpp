void modssl_var_extract_dns(apr_table_t *t, SSL *ssl, apr_pool_t *p)
{
    apr_hash_t *nids;
    unsigned n;
    X509 *xs;

    /* Build up a hash table of (int *)NID->(char *)short-name for all
     * the tags which are to be extracted: */
    nids = apr_hash_make(p);
    for (n = 0; ssl_var_lookup_ssl_cert_dn_rec[n].name; n++) {
        if (ssl_var_lookup_ssl_cert_dn_rec[n].extract) {
            apr_hash_set(nids, &ssl_var_lookup_ssl_cert_dn_rec[n].nid,
                         sizeof(ssl_var_lookup_ssl_cert_dn_rec[0].nid),
                         ssl_var_lookup_ssl_cert_dn_rec[n].name);
        }
    }
    
    /* Extract the server cert DNS -- note that the refcount does NOT
     * increase: */
    xs = SSL_get_certificate(ssl);
    if (xs) {
        extract_dn(t, nids, "SSL_SERVER_S_DN_", X509_get_subject_name(xs), p);
        extract_dn(t, nids, "SSL_SERVER_I_DN_", X509_get_issuer_name(xs), p);
    }
    
    /* Extract the client cert DNs -- note that the refcount DOES
     * increase: */
    xs = SSL_get_peer_certificate(ssl);
    if (xs) {
        extract_dn(t, nids, "SSL_CLIENT_S_DN_", X509_get_subject_name(xs), p);
        extract_dn(t, nids, "SSL_CLIENT_I_DN_", X509_get_issuer_name(xs), p);
        X509_free(xs);
    }
}