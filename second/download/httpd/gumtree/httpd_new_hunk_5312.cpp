    X509_free(issuer);
    if (!cinf->cid)
        return 0;
    X509_digest(x, EVP_sha1(), cinf->idx, NULL);

    aia = X509_get1_ocsp(x);
    if (aia) {
        cinf->uri = sk_OPENSSL_STRING_pop(aia);
        X509_email_free(aia);
    }
    if (!cinf->uri && !mctx->stapling_force_url) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02218)
                     "ssl_stapling_init_cert: no responder URL");
        return 0;
    }
    return 1;
}

static certinfo *stapling_get_cert_info(server_rec *s, modssl_ctx_t *mctx,
                                        SSL *ssl)
{
