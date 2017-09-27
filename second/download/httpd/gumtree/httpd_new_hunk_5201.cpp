    } else {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01902)
                     "Host %s: X.509 CRL storage locations configured, "
                     "but CRL checking (%sCARevocationCheck) is not "
                     "enabled", mctx->sc->vhost_id, cfgp);
    }

    return APR_SUCCESS;
}

static apr_status_t ssl_init_ctx_cert_chain(server_rec *s,
                                            apr_pool_t *p,
                                            apr_pool_t *ptemp,
                                            modssl_ctx_t *mctx)
{
    BOOL skip_first = FALSE;
    int i, n;
    const char *chain = mctx->cert_chain;

    /*
     * Optionally configure extra server certificate chain certificates.
     * This is usually done by OpenSSL automatically when one of the
     * server cert issuers are found under SSLCACertificatePath or in
     * SSLCACertificateFile. But because these are intended for client
     * authentication it can conflict. For instance when you use a
