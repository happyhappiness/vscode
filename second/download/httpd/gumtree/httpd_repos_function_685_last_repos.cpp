static void ssl_check_public_cert(server_rec *s,
                                  apr_pool_t *ptemp,
                                  X509 *cert,
                                  const char *key_id)
{
    int is_ca, pathlen;

    if (!cert) {
        return;
    }

    /*
     * Some information about the certificate(s)
     */

    if (modssl_X509_getBC(cert, &is_ca, &pathlen)) {
        if (is_ca) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01906)
                         "%s server certificate is a CA certificate "
                         "(BasicConstraints: CA == TRUE !?)", key_id);
        }

        if (pathlen > 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01907)
                         "%s server certificate is not a leaf certificate "
                         "(BasicConstraints: pathlen == %d > 0 !?)",
                         key_id, pathlen);
        }
    }

    if (modssl_X509_match_name(ptemp, cert, (const char *)s->server_hostname,
                               TRUE, s) == FALSE) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01909)
                     "%s server certificate does NOT include an ID "
                     "which matches the server name", key_id);
    }
}