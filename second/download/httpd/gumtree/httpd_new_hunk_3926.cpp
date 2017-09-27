     * back to "blocking" here ensures such operations don't fail with
     * SSL_ERROR_WANT_READ. */
    inctx->block = APR_BLOCK_READ;

    /* Handle custom errors. */
    if (status != APR_SUCCESS) {
        return ssl_io_filter_error(f, bb, status, 0);
    }

    /* Create a transient bucket out of the decrypted data. */
    if (len > 0) {
        apr_bucket *bucket =
            apr_bucket_transient_create(start, len, f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, bucket);
    }

    return APR_SUCCESS;
}


/* ssl_io_filter_output() produces one SSL/TLS message per bucket
 * passed down the output filter stack.  This results in a high
