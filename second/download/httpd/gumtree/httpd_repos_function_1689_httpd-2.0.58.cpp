static apr_status_t xlate_out_filter(ap_filter_t *f, apr_bucket_brigade *bb)
{
    charset_req_t *reqinfo = ap_get_module_config(f->r->request_config,
                                                  &charset_lite_module);
    charset_dir_t *dc = ap_get_module_config(f->r->per_dir_config,
                                             &charset_lite_module);
    charset_filter_ctx_t *ctx = f->ctx;
    apr_bucket *dptr, *consumed_bucket;
    const char *cur_str;
    apr_size_t cur_len, cur_avail;
    char tmp[OUTPUT_XLATE_BUF_SIZE];
    apr_size_t space_avail;
    int done;
    apr_status_t rv = APR_SUCCESS;

    if (!ctx) { 
        /* this is SetOutputFilter path; grab the preallocated context,
         * if any; note that if we decided not to do anything in an earlier
         * handler, we won't even have a reqinfo
         */
        if (reqinfo) {
            ctx = f->ctx = reqinfo->output_ctx;
            reqinfo->output_ctx = NULL; /* prevent SNAFU if user coded us twice
                                         * in the filter chain; we can't have two
                                         * instances using the same context
                                         */
        }
        if (!ctx) {                   /* no idea how to translate; don't do anything */
            ctx = f->ctx = apr_pcalloc(f->r->pool, sizeof(charset_filter_ctx_t));
            ctx->dc = dc;
            ctx->noop = 1;
        }
    }

    if (dc->debug >= DBGLVL_GORY) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                     "xlate_out_filter() - "
                     "charset_source: %s charset_default: %s",
                     dc && dc->charset_source ? dc->charset_source : "(none)",
                     dc && dc->charset_default ? dc->charset_default : "(none)");
    }

    if (!ctx->ran) {  /* filter never ran before */
        chk_filter_chain(f);
        ctx->ran = 1;
    }

    if (ctx->noop) {
        return ap_pass_brigade(f->next, bb);
    }

    dptr = APR_BRIGADE_FIRST(bb);
    done = 0;
    cur_len = 0;
    space_avail = sizeof(tmp);
    consumed_bucket = NULL;
    while (!done) {
        if (!cur_len) { /* no bytes left to process in the current bucket... */
            if (consumed_bucket) {
                apr_bucket_delete(consumed_bucket);
                consumed_bucket = NULL;
            }
            if (dptr == APR_BRIGADE_SENTINEL(bb)) {
                done = 1;
                break;
            }
            if (APR_BUCKET_IS_EOS(dptr)) {
                done = 1;
                cur_len = -1; /* XXX yuck, but that tells us to send
                                 * eos down; when we minimize our bb construction
                                 * we'll fix this crap */
                if (ctx->saved) {
                    /* Oops... we have a partial char from the previous bucket
                     * that won't be completed because there's no more data.
                     */
                    rv = APR_INCOMPLETE;
                    ctx->ees = EES_INCOMPLETE_CHAR;
                }
                break;
            }
            rv = apr_bucket_read(dptr, &cur_str, &cur_len, APR_BLOCK_READ);
            if (rv != APR_SUCCESS) {
                done = 1;
                ctx->ees = EES_BUCKET_READ;
                break;
            }
            consumed_bucket = dptr; /* for axing when we're done reading it */
            dptr = APR_BUCKET_NEXT(dptr); /* get ready for when we access the 
                                          * next bucket */
        }
        /* Try to fill up our tmp buffer with translated data. */
        cur_avail = cur_len;

        if (cur_len) { /* maybe we just hit the end of a pipe (len = 0) ? */
            if (ctx->saved) {
                /* Rats... we need to finish a partial character from the previous
                 * bucket.
                 */
                char *tmp_tmp;
                
                tmp_tmp = tmp + sizeof(tmp) - space_avail;
                rv = finish_partial_char(ctx,
                                         &cur_str