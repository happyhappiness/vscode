static void ssl_check_public_cert(server_rec *s,
                                  apr_pool_t *ptemp,
                                  X509 *cert,
                                  int type)
{
    int is_ca, pathlen;
    char *cn;

    if (!cert) {
        return;
    }

    /*
     * Some information about the certificate(s)
     */

    if (SSL_X509_isSGC(cert)) {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                     "%s server certificate enables "
                     "Server Gated Cryptography (SGC)",
                     ssl_asn1_keystr(type));
    }

    if (SSL_X509_getBC(cert, &is_ca, &pathlen)) {
        if (is_ca) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "%s server certificate is a CA certificate "
                         "(BasicConstraints: CA == TRUE !?)",
                         ssl_asn1_keystr(type));
        }

        if (pathlen > 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "%s server certificate is not a leaf certificate "
                         "(BasicConstraints: pathlen == %d > 0 !?)",
                         ssl_asn1_keystr(type), pathlen);
        }
    }

    if (SSL_X509_getCN(ptemp, cert, &cn)) {
        int fnm_flags = APR_FNM_PERIOD|APR_FNM_CASE_BLIND;

        if (apr_fnmatch_test(cn)) {
            if (apr_fnmatch(cn, s->server_hostname,
                            fnm_flags) == APR_FNM_NOMATCH) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                             "%s server certificate wildcard CommonName "
                             "(CN) `%s' does NOT match server name!?",
                             ssl_asn1_keystr(type), cn);
            }
        }
        else if (strNE(s->server_hostname, cn)) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "%s server certificate CommonName (CN) `%s' "
                         "does NOT match server name!?",
                         ssl_asn1_keystr(type), cn);
        }
    }
}