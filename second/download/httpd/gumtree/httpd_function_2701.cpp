static int xlate_in_filter(ap_filter_t *f, apr_bucket_brigade *bb,
                           ap_input_mode_t mode, apr_read_type_e block,
                           apr_off_t readbytes)
{
    apr_status_t rv;
    charset_req_t *reqinfo = ap_get_module_config(f->r->request_config,
                                                  &charset_lite_module);
    charset_dir_t *dc = ap_get_module_config(f->r->per_dir_config,
                                             &charset_lite_module);
    charset_filter_ctx_t *ctx = f->ctx;
    apr_size_t buffer_size;
    int hit_eos;

    if (!ctx) {
        /* this is SetInputFilter path; grab the preallocated context,
         * if any; note that if we decided not to do anything in an earlier
         * handler, we won't even have a reqinfo
         */
        if (reqinfo) {
            ctx = f->ctx = reqinfo->input_ctx;
            reqinfo->input_ctx = NULL; /* prevent SNAFU if user coded us twice
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
                     "xlate_in_filter() - "
                     "charset_source: %s charset_default: %s",
                     dc && dc->charset_source ? dc->charset_source : "(none)",
                     dc && dc->charset_default ? dc->charset_default : "(none)");
    }

    if (!ctx->ran) {  /* filter never ran before */
        chk_filter_chain(f);
        ctx->ran = 1;
        if (!ctx->noop && !ctx->is_sb
            && apr_table_get(f->r->headers_in, "Content-Length")) {
            /* A Content-Length header is present, but it won't be valid after
             * conversion because we're not converting between two single-byte
             * charsets.  This will affect most CGI scripts and may affect
             * some modules.
             * Content-Length can't be unset here because that would break
             * being able to read the request body.
             * Processing of chunked request bodies is not impacted by this
             * filter since the the length was not declared anyway.
             */
            if (dc->debug >= DBGLVL_PMC) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                              "Request body length may change, resulting in "
                              "misprocessing by some modules or scripts");
            }
        }
    }

    if (ctx->noop) {
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    if (APR_BRIGADE_EMPTY(ctx->bb)) {
        if ((rv = ap_get_brigade(f->next, bb, mode, block,
                                 readbytes)) != APR_SUCCESS) {
            return rv;
        }
    }
    else {
        APR_BRIGADE_PREPEND(bb, ctx->bb); /* first use the leftovers */
    }

    buffer_size = INPUT_XLATE_BUF_SIZE;
    rv = xlate_brigade(ctx, bb, ctx->tmp, &buffer_size, &hit_eos);
    if (rv == APR_SUCCESS) {
        if (!hit_eos) {
            /* move anything leftover into our context for next time;
             * we don't currently "set aside" since the data came from
             * down below, but I suspect that for long-term we need to
             * do that
             */
            APR_BRIGADE_CONCAT(ctx->bb, bb);
        }
        if (buffer_size < INPUT_XLATE_BUF_SIZE) { /* do we have output? */
            apr_bucket *e;

            e = apr_bucket_heap_create(ctx->tmp,
                                       INPUT_XLATE_BUF_SIZE - buffer_size,
                                       NULL, f->r->connection->bucket_alloc);
            /* make sure we insert at the head, because there may be
             * an eos bucket already there, and the eos bucket should
             * come after the data
             */
            APR_BRIGADE_INSERT_HEAD(bb, e);
        }
        else {
            /* XXX need to get some more data... what if the last brigade
             * we got had only the first byte of a multibyte char?  we need
             * to grab more data from the network instead of returning an
             * empty brigade
             */
        }
    }
    else {
        log_xlate_error(f, rv);
    }

    return rv;
}