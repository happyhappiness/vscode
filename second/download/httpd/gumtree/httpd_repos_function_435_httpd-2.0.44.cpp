static apr_status_t logio_out_filter(ap_filter_t *f,
                                     apr_bucket_brigade *bb) {
    apr_bucket *b = APR_BRIGADE_LAST(bb);

    /* End of data, make sure we flush */
    if (APR_BUCKET_IS_EOS(b)) {
        APR_BRIGADE_INSERT_TAIL(bb,
                                apr_bucket_flush_create(f->c->bucket_alloc));
        APR_BUCKET_REMOVE(b);
        apr_bucket_destroy(b);
    }

    return ap_pass_brigade(f->next, bb);
}