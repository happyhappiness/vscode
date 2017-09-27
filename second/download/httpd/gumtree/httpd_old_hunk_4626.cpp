        SSL_CTX_set_tmp_ecdh(mctx->ssl_ctx, eckey);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02541)
                     "ECDH curve %s for %s specified in %s",
                     OBJ_nid2sn(nid), vhost_id, certfile);
    }
    /*
     * ...otherwise, enable auto curve selection (OpenSSL 1.0.2 and later)
     * or configure NIST P-256 (required to enable ECDHE for earlier versions)
     */
    else {
#if defined(SSL_CTX_set_ecdh_auto)
        SSL_CTX_set_ecdh_auto(mctx->ssl_ctx, 1);
#else
        SSL_CTX_set_tmp_ecdh(mctx->ssl_ctx,
                             EC_KEY_new_by_curve_name(NID_X9_62_prime256v1));
#endif
    }
    EC_KEY_free(eckey);
    EC_GROUP_free(ecparams);
#endif

    return APR_SUCCESS;
}
