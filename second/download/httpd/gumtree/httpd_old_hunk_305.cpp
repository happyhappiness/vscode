
    if (pkp->cert_path) {
        SSL_X509_INFO_load_path(ptemp, sk, pkp->cert_path);
    }

    if ((ncerts = sk_X509_INFO_num(sk)) > 0) {
        ssl_log(s, SSL_LOG_TRACE|SSL_INIT,
                "loaded %d client certs for SSL proxy",
                ncerts);

        pkp->certs = sk;
    }
    else {
        ssl_log(s, SSL_LOG_WARN|SSL_INIT,
                "no client certs found for SSL proxy");
        sk_X509_INFO_free(sk);
    }
}

static void ssl_init_proxy_ctx(server_rec *s,
                               apr_pool_t *p,
