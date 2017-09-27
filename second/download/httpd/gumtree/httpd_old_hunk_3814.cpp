        if (strEQ(APR_ARRAY_IDX(mctx->pks->cert_files, i, const char *), chain)) {
            skip_first = TRUE;
            break;
        }
    }

    n = SSL_CTX_use_certificate_chain(mctx->ssl_ctx,
                                      (char *)chain,
                                      skip_first, NULL);
    if (n < 0) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01903)
                "Failed to configure CA certificate chain!");
        return ssl_die(s);
    }

