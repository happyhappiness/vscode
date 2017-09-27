     * back to "blocking" here ensures such operations don't fail with
     * SSL_ERROR_WANT_READ. */
    inctx->block = APR_BLOCK_READ;

    /* Handle custom errors. */
    if (status != APR_SUCCESS) {
        return ssl_io_filter_error(f, bb, status);
    }

    /* Create a transient bucket out of the decrypted data. */
    if (len > 0) {
        apr_bucket *bucket =
            apr_bucket_transient_create(start, len, f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, bucket);
    }

#ifdef HAVE_TLS_ALPN
    /* By this point, Application-Layer Protocol Negotiation (ALPN) should be 
     * completed (if our version of OpenSSL supports it). If we haven't already, 
     * find out which protocol was decided upon and inform other modules 
     * by calling alpn_proto_negotiated_hook. 
     */
    if (!inctx->alpn_finished) {
        SSLConnRec *sslconn = myConnConfig(f->c);
        const unsigned char *next_proto = NULL;
        unsigned next_proto_len = 0;
        const char *protocol;

        SSL_get0_alpn_selected(inctx->ssl, &next_proto, &next_proto_len);
        if (next_proto && next_proto_len) {
            protocol = apr_pstrmemdup(f->c->pool, (const char *)next_proto,
                                       next_proto_len);
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, f->c,
                          APLOGNO(02836) "ALPN selected protocol: '%s'",
                          protocol);
            
            if (strcmp(protocol, ap_get_protocol(f->c))) {
                status = ap_switch_protocol(f->c, NULL, sslconn->server,
                                            protocol);
                if (status != APR_SUCCESS) {
                    ap_log_cerror(APLOG_MARK, APLOG_ERR, status, f->c,
                                  APLOGNO(02908) "protocol switch to '%s' failed",
                                  protocol);
                    return status;
                }
            }
        }
        inctx->alpn_finished = 1;
    }
#endif

    return APR_SUCCESS;
}


/* ssl_io_filter_output() produces one SSL/TLS message per bucket
 * passed down the output filter stack.  This results in a high
