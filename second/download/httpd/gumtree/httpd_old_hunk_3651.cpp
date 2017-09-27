        issuer = NULL;
    X509_STORE_CTX_cleanup(&inctx);
    return issuer;

}

int ssl_stapling_init_cert(server_rec *s, modssl_ctx_t *mctx, X509 *x)
{
    certinfo *cinf;
    X509 *issuer = NULL;
    STACK_OF(OPENSSL_STRING) *aia = NULL;

    if (x == NULL)
        return 0;
    cinf  = X509_get_ex_data(x, stapling_ex_idx);
    if (cinf) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02215)
                     "ssl_stapling_init_cert: certificate already initialized!");
        return 0;
    }
    cinf = OPENSSL_malloc(sizeof(certinfo));
    if (!cinf) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02216)
                     "ssl_stapling_init_cert: error allocating memory!");
        return 0;
    }
    cinf->cid = NULL;
    cinf->uri = NULL;
    X509_set_ex_data(x, stapling_ex_idx, cinf);

    issuer = stapling_get_issuer(mctx, x);

    if (issuer == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02217)
                     "ssl_stapling_init_cert: Can't retrieve issuer certificate!");
        return 0;
    }

    cinf->cid = OCSP_cert_to_id(NULL, x, issuer);
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
    certinfo *cinf;
    X509 *x;
    x = SSL_get_certificate(ssl);
    if (x == NULL)
        return NULL;
    cinf = X509_get_ex_data(x, stapling_ex_idx);
    if (cinf && cinf->cid)
        return cinf;
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01926)
                 "stapling_get_cert_info: stapling not supported for certificate");
    return NULL;
}

/*
 * OCSP response caching code. The response is preceded by a flag value
 * which indicates whether the response was invalid when it was stored.
