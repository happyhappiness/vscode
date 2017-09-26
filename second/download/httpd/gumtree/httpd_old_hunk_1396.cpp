    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "loaded %d client certs for SSL proxy",
                 ncerts);
    pkp->certs = sk;
}

static void ssl_init_proxy_ctx(server_rec *s,
                               apr_pool_t *p,
                               apr_pool_t *ptemp,
                               SSLSrvConfigRec *sc)
