        SSL_CTX_set_tmp_ecdh(mctx->ssl_ctx, eckey);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02541)
                     "ECDH curve %s for %s specified in %s",
                     OBJ_nid2sn(nid), vhost_id, certfile);
    }
    /*
     * ...otherwise, enable auto curve selection (OpenSSL 1.0.2)
     * or configure NIST P-256 (required to enable ECDHE for earlier versions)
     * ECDH is always enabled in 1.1.0 unless excluded from SSLCipherList
     */
#if (OPENSSL_VERSION_NUMBER < 0x10100000L)
    else {
#if defined(SSL_CTX_set_ecdh_auto)
        SSL_CTX_set_ecdh_auto(mctx->ssl_ctx, 1);
#else
        SSL_CTX_set_tmp_ecdh(mctx->ssl_ctx,
                             EC_KEY_new_by_curve_name(NID_X9_62_prime256v1));
#endif
    }
#endif
    /* OpenSSL assures us that _free() is NULL-safe */
    EC_KEY_free(eckey);
    EC_GROUP_free(ecparams);
#endif

    return APR_SUCCESS;
}
