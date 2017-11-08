static certinfo *stapling_get_certinfo(server_rec *s, modssl_ctx_t *mctx,
                                        SSL *ssl)
{
    certinfo *cinf;
    X509 *x;
    UCHAR idx[SHA_DIGEST_LENGTH];
    x = SSL_get_certificate(ssl);
    if ((x == NULL) || (X509_digest(x, EVP_sha1(), idx, NULL) != 1))
        return NULL;
    cinf = apr_hash_get(stapling_certinfo, idx, sizeof(idx));
    if (cinf && cinf->cid)
        return cinf;
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01926)
                 "stapling_get_certinfo: stapling not supported for certificate");
    return NULL;
}