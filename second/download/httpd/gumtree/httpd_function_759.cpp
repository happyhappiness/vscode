static apr_status_t ssl_io_filter_buffer(ap_filter_t *f,
                                         apr_bucket_brigade *bb,
                                         ap_input_mode_t mode,
                                         apr_read_type_e block,
                                         apr_off_t bytes)
{
    struct modssl_buffer_ctx *ctx = f->ctx;
    apr_status_t rv;

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                  "read from buffered SSL brigade, mode %d, "
                  "%" APR_OFF_T_FMT " bytes",
                  mode, bytes);

    if (mode != AP_MODE_READBYTES && mode != AP_MODE_GETLINE) {
        return APR_ENOTIMPL;
    }

    if (mode == AP_MODE_READBYTES) {
        apr_bucket *e;

        /* Partition the buffered brigade. */
        rv = apr_brigade_partition(ctx->bb, bytes, &e);
        if (rv && rv != APR_INCOMPLETE) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r,
                          "could not partition buffered SSL brigade");
            ap_remove_input_filter(f);
            return rv;
        }

        /* If the buffered brigade contains less then the requested
         * length, just pass it all back. */
        if (rv == APR_INCOMPLETE) {
            APR_BRIGADE_CONCAT(bb, ctx->bb);
        } else {
            apr_bucket *d = APR_BRIGADE_FIRST(ctx->bb);

            e = APR_BUCKET_PREV(e);
            
            /* Unsplice the partitioned segment and move it into the
             * passed-in brigade; no convenient way to do this with
             * the APR_BRIGADE_* macros. */
            APR_RING_UNSPLICE(d, e, link);
            APR_RING_SPLICE_HEAD(&bb->list, d, e, apr_bucket, link);

            APR_BRIGADE_CHECK_CONSISTENCY(bb);
            APR_BRIGADE_CHECK_CONSISTENCY(ctx->bb);
        }
    }
    else {
        /* Split a line into the passed-in brigade. */
        rv = apr_brigade_split_line(bb, ctx->bb, mode, bytes);

        if (rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r,
                          "could not split line from buffered SSL brigade");
            ap_remove_input_filter(f);
            return rv;
        }
    }

    if (APR_BRIGADE_EMPTY(ctx->bb)) {
        apr_bucket *e = APR_BRIGADE_LAST(bb);
        
        /* Ensure that the brigade is terminated by an EOS if the
         * buffered request body has been entirely consumed. */
        if (e == APR_BRIGADE_SENTINEL(bb) || !APR_BUCKET_IS_EOS(e)) {
            e = apr_bucket_eos_create(f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, e);
        }

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                      "buffered SSL brigade now exhausted; removing filter");
        ap_remove_input_filter(f);
    }

    return APR_SUCCESS;
}