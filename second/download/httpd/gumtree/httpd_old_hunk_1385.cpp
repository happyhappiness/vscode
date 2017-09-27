    }

    /*
     *  Check for problematic re-initializations
     */
    if (mctx->pks->certs[SSL_AIDX_RSA] ||
        mctx->pks->certs[SSL_AIDX_DSA])
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                "Illegal attempt to re-initialise SSL for server "
                "(SSLEngine On should go in the VirtualHost, not in global scope.)");
        ssl_die();
    }
