static apr_status_t data_out_filter(ap_filter_t *f, apr_bucket_brigade *bb)
{
    apr_bucket *e, *ee;
    request_rec *r = f->r;
    data_ctx *ctx = f->ctx;
    apr_status_t rv = APR_SUCCESS;

    /* first time in? create a context */
    if (!ctx) {
        char *type;
        char *charset = NULL;
        char *end;
        const char *content_length;

        /* base64-ing won't work on subrequests, it would be nice if
         * it did. Within subrequests, we have no EOS to check for,
         * so we don't know when to flush the tail to the network.
         */
        if (!ap_is_initial_req(f->r)) {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        ctx = f->ctx = apr_pcalloc(r->pool, sizeof(*ctx));
        ctx->bb = apr_brigade_create(r->pool, f->c->bucket_alloc);

        type = apr_pstrdup(r->pool, r->content_type);
        if (type) {
            charset = strchr(type, ' ');
            if (charset) {
                *charset++ = 0;
                end = strchr(charset, ' ');
                if (end) {
                    *end++ = 0;
                }
            }
        }

        apr_brigade_printf(ctx->bb, NULL, NULL, "data:%s%s;base64,",
                type ? type : "", charset ? charset : "");

        content_length = apr_table_get(r->headers_out, "Content-Length");
        if (content_length) {
            apr_off_t len, clen;
            apr_brigade_length(ctx->bb, 1, &len);
            clen = apr_atoi64(content_length);
            if (clen >= 0 && clen < APR_INT32_MAX) {
                ap_set_content_length(r, len + apr_base64_encode_len(clen) - 1);
            }
            else {
                apr_table_unset(r->headers_out, "Content-Length");
            }
        }

        ap_set_content_type(r, "text/plain");

    }

    /* Do nothing if asked to filter nothing. */
    if (APR_BRIGADE_EMPTY(bb)) {
        return ap_pass_brigade(f->next, bb);
    }

    while (APR_SUCCESS == rv && !APR_BRIGADE_EMPTY(bb)) {
        const char *data;
        apr_size_t size;
        apr_size_t tail;
        apr_size_t len;
        /* buffer big enough for 8000 encoded bytes (6000 raw bytes) and terminator */
        char buffer[APR_BUCKET_BUFF_SIZE + 1];
        char encoded[((sizeof(ctx->overflow)) / 3) * 4 + 1];

        e = APR_BRIGADE_FIRST(bb);

        /* EOS means we are done. */
        if (APR_BUCKET_IS_EOS(e)) {

            /* write away the tail */
            if (ctx->count) {
                len = apr_base64_encode_binary(encoded, ctx->overflow,
                        ctx->count);
                apr_brigade_write(ctx->bb, NULL, NULL, encoded, len - 1);
                ctx->count = 0;
            }

            /* pass the EOS across */
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, e);

            /* pass what we have down the chain */
            ap_remove_output_filter(f);
            rv = ap_pass_brigade(f->next, ctx->bb);

            /* pass any stray buckets after the EOS down the stack */
            if ((APR_SUCCESS == rv) && (!APR_BRIGADE_EMPTY(bb))) {
               rv = ap_pass_brigade(f->next, bb);
            }
            continue;
        }

        /* flush what we can, we can't flush the tail until EOS */
        if (APR_BUCKET_IS_FLUSH(e)) {

            /* pass the flush bucket across */
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, e);

            /* pass what we have down the chain */
            rv = ap_pass_brigade(f->next, ctx->bb);
            continue;
        }

        /* metadata buckets are preserved as is */
        if (APR_BUCKET_IS_METADATA(e)) {
            /*
             * Remove meta data bucket from old brigade and insert into the
             * new.
             */
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, e);
            continue;
        }

        /* make sure we don't read more than 6000 bytes at a time */
        apr_brigade_partition(bb, (APR_BUCKET_BUFF_SIZE / 4 * 3), &ee);

        /* size