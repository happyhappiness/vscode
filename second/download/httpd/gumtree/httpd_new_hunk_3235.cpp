        mctx->stapling_errcache_timeout = 600;
    }
    if (mctx->stapling_responder_timeout == UNSET) {
        mctx->stapling_responder_timeout = 10 * APR_USEC_PER_SEC;
    }
    SSL_CTX_set_tlsext_status_cb(ctx, stapling_cb);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01960) "OCSP stapling initialized");
}

#endif
