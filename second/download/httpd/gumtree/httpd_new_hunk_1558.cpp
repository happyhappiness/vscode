    apr_bucket *bkt;
    request_rec *r = f->r;
    deflate_ctx *ctx = f->ctx;
    int zRC;
    apr_status_t rv;
    deflate_filter_config *c;

    /* just get out of the way of things we don't want. */
    if (mode != AP_MODE_READBYTES) {
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    c = ap_get_module_config(r->server->module_config, &deflate_module);

    if (!ctx) {
        char deflate_hdr[10];
        apr_size_t len;

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

        rv = ap_get_brigade(f->next, ctx->bb, AP_MODE_READBYTES, block, 10);
        if (rv != APR_SUCCESS) {
            return rv;
        }

        apr_table_unset(r->headers_in, "Content-Length");
        apr_table_unset(r->headers_in, "Content-MD5");

        len = 10;
        rv = apr_brigade_flatten(ctx->bb, deflate_hdr, &len);
        if (rv != APR_SUCCESS) {
            return rv;
        }

        /* We didn't get the magic bytes. */
        if (len != 10 ||
            deflate_hdr[0] != deflate_magic[0] ||
            deflate_hdr[1] != deflate_magic[1]) {
            return APR_EGENERAL;
        }

        /* We can't handle flags for now. */
        if (deflate_hdr[3] != 0) {
            return APR_EGENERAL;
        }

        zRC = inflateInit2(&ctx->stream, c->windowSize);

        if (zRC != Z_OK) {
