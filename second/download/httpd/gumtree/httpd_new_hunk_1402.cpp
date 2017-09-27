    apr_bucket *bkt;
    request_rec *r = f->r;
    deflate_ctx *ctx = f->ctx;
    int zRC;
    apr_status_t rv;
    deflate_filter_config *c;
    deflate_dirconf_t *dc;
    apr_off_t inflate_limit;

    /* just get out of the way of things we don't want. */
    if (mode != AP_MODE_READBYTES) {
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    c = ap_get_module_config(r->server->module_config, &deflate_module);
    dc = ap_get_module_config(r->per_dir_config, &deflate_module);

    if (!ctx || ctx->header_len < sizeof(ctx->header)) {
        apr_size_t len;

        if (!ctx) {
            /* only work on main request/no subrequests */
            if (!ap_is_initial_req(r)) {
                ap_remove_input_filter(f);
                return ap_get_brigade(f->next, bb, mode, block, readbytes);
            }

            /* We can't operate on Content-Ranges */
            if (apr_table_get(r->headers_in, "Content-Range") != NULL) {
                ap_remove_input_filter(f);
                return ap_get_brigade(f->next, bb, mode, block, readbytes);
            }

            /* Check whether request body is gzipped.
             *
             * If it is, we're transforming the contents, invalidating
             * some request headers including Content-Encoding.
             *
             * If not, we just remove ourself.
             */
            if (check_gzip(r, r->headers_in, NULL) == 0) {
                ap_remove_input_filter(f);
                return ap_get_brigade(f->next, bb, mode, block, readbytes);
            }

            f->ctx = ctx = apr_pcalloc(f->r->pool, sizeof(*ctx));
            ctx->bb = apr_brigade_create(r->pool, f->c->bucket_alloc);
            ctx->proc_bb = apr_brigade_create(r->pool, f->c->bucket_alloc);
            ctx->buffer = apr_palloc(r->pool, c->bufferSize);
        }

        do {
            apr_brigade_cleanup(ctx->bb);

            len = sizeof(ctx->header) - ctx->header_len;
            rv = ap_get_brigade(f->next, ctx->bb, AP_MODE_READBYTES, block,
                                len);

            /* ap_get_brigade may return success with an empty brigade for
             * a non-blocking read which would block (an empty brigade for
             * a blocking read is an issue which is simply forwarded here).
             */
            if (rv != APR_SUCCESS || APR_BRIGADE_EMPTY(ctx->bb)) {
                return rv;
            }

            /* zero length body? step aside */
            bkt = APR_BRIGADE_FIRST(ctx->bb);
            if (APR_BUCKET_IS_EOS(bkt)) {
                if (ctx->header_len) {
                    /* If the header was (partially) read it's an error, this
                     * is not a gzip Content-Encoding, as claimed.
                     */
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Encountered premature end-of-stream while "
                                  "reading inflate header");
                    return APR_EGENERAL;
                }
                APR_BUCKET_REMOVE(bkt);
                APR_BRIGADE_INSERT_TAIL(bb, bkt);
                ap_remove_input_filter(f);
                return APR_SUCCESS;
            }

            rv = apr_brigade_flatten(ctx->bb,
                                     ctx->header + ctx->header_len, &len);
            if (rv != APR_SUCCESS) {
                return rv;
            }
            if (len && !ctx->header_len) {
                apr_table_unset(r->headers_in, "Content-Length");
                apr_table_unset(r->headers_in, "Content-MD5");
            }
            ctx->header_len += len;

        } while (ctx->header_len < sizeof(ctx->header));

        /* We didn't get the magic bytes. */
        if (ctx->header[0] != deflate_magic[0] ||
            ctx->header[1] != deflate_magic[1]) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "Zlib: Invalid header");
            return APR_EGENERAL;
        }

        ctx->zlib_flags = ctx->header[3];
        if ((ctx->zlib_flags & RESERVED)) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "Zlib: Invalid flags %02x", ctx->zlib_flags);
            return APR_EGENERAL;
        }

        zRC = inflateInit2(&ctx->stream, c->windowSize);

        if (zRC != Z_OK) {
