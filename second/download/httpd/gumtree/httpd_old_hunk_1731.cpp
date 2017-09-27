      || mctx->pks->certs[SSL_AIDX_ECC]
#endif
        )
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                "Illegal attempt to re-initialise SSL for server "
                "(SSLEngine On should go in the VirtualHost, not in global scope.)");
        ssl_die();
    }
}

#ifndef OPENSSL_NO_TLSEXT
static void ssl_init_ctx_tls_extensions(server_rec *s,
