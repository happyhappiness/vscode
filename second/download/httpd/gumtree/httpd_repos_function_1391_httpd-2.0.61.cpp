static apr_status_t deflate_out_filter(ap_filter_t *f,
                                       apr_bucket_brigade *bb)
{
    apr_bucket *e;
    request_rec *r = f->r;
    deflate_ctx *ctx = f->ctx;
    int zRC;
    deflate_filter_config *c = ap_get_module_config(r->server->module_config,
                                                    &deflate_module);

    /* If we don't have a context, we need to ensure that it is okay to send
     * the deflated content.  If we have a context, that means we've done
     * this before and we liked it.
     * This could be not so nice if we always fail.  But, if we succeed,
     * we're in better shape.
     */
    if (!ctx) {
        char *buf, *token;
        const char *encoding, *accepts;

        /* only work on main request/no subrequests */
        if (r->main) {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        /* some browsers might have problems, so set no-gzip
         * (with browsermatch) for them
         */
        if (apr_table_get(r->subprocess_env, "no-gzip")) {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        /* Some browsers might have problems with content types
         * other than text/html, so set gzip-only-text/html
         * (with browsermatch) for them
         */
        if (r->content_type == NULL
             || strncmp(r->content_type, "text/html", 9)) {
            const char *env_value = apr_table_get(r->subprocess_env,
                                                  "gzip-only-text/html");
            if ( env_value && (strcmp(env_value,"1") == 0) ) {
                ap_remove_output_filter(f);
                return ap_pass_brigade(f->next, bb);
            }            
        }

        /* Let's see what our current Content-Encoding is.
         * If it's already encoded, don't compress again.
         * (We could, but let's not.)
         */
        encoding = apr_table_get(r->headers_out, "Content-Encoding");
        if (encoding) {
            const char *err_enc;

            err_enc = apr_table_get(r->err_headers_out, "Content-Encoding");
            if (err_enc) {
                encoding = apr_pstrcat(r->pool, encoding, ",", err_enc, NULL);
            }
        }
        else {
            encoding = apr_table_get(r->err_headers_out, "Content-Encoding");
        }

        if (r->content_encoding) {
            encoding = encoding ? apr_pstrcat(r->pool, encoding, ",",
                                              r->content_encoding, NULL)
                                : r->content_encoding;
        }

        if (encoding) {
            const char *tmp = encoding;

            token = ap_get_token(r->pool, &tmp, 0);
            while (token && *token) {
                /* stolen from mod_negotiation: */
                if (strcmp(token, "identity") && strcmp(token, "7bit") &&
                    strcmp(token, "8bit") && strcmp(token, "binary")) {

                    ap_remove_output_filter(f);
                    return ap_pass_brigade(f->next, bb);			
                }

                /* Otherwise, skip token */
                if (*tmp) {
                    ++tmp;
                }
                token = (*tmp) ? ap_get_token(r->pool, &tmp, 0) : NULL;
            }
        }

        /* Even if we don't accept this request based on it not having
         * the Accept-Encoding, we need to note that we were looking
         * for this header and downstream proxies should be aware of that.
         */
        apr_table_mergen(r->headers_out, "Vary", "Accept-Encoding");

        /* if they don't have the line, then they can't play */
        accepts = apr_table_get(r->headers_in, "Accept-Encoding");
        if (accepts == NULL) {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        token = ap_get_token(r->pool, &accepts, 0);
        while (token && token[0] && strcasecmp(token, "gzip")) {
            /* skip parameters, XXX: ;q=foo evaluation? */
            while (*accepts == ';') { 
                ++accepts;
                token = ap_get_token(r->pool, &accepts, 1);
            }

            /* retrieve next token */
            if (*accepts == ',') {
                ++accepts;
            }
            token = (*accepts) ? ap_get_token(r->pool, &accepts, 0) : NULL;
        }

        /* No acceptable token found. */
        if (token == NULL || token[0] == '\0') {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        /* We're cool with filtering this. */
        ctx = f->ctx = apr_pcalloc(r->pool, sizeof(*ctx));
        ctx->bb = apr_brigade_create(r->pool, f->c->bucket_alloc);
        ctx->buffer = apr_palloc(r->pool, c->bufferSize);

        zRC = deflateInit2(&ctx->stream, c->compressionlevel, Z_DEFLATED,
                           c->windowSize, c->memlevel,
                           Z_DEFAULT_STRATEGY);

        if (zRC != Z_OK) {
            f->ctx = NULL;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "unable to init Zlib: "
                          "deflateInit2 returned %d: URL %s",
                          zRC, r->uri);
            return ap_pass_brigade(f->next, bb);
        }

        /* RFC 1952 Section 2.3 dictates the gzip header:
         *
         * +---+---+---+---+---+---+---+---+---+---+
         * |ID1|ID2|CM |FLG|     MTIME     |XFL|OS |
         * +---+---+---+---+---+---+---+---+---+---+
         *
         * If we wish to populate in MTIME (as hinted in RFC 1952), do:
         * putLong(date_array, apr_time_now() / APR_USEC_PER_SEC);
         * where date_array is a char[4] and then print date_array in the
         * MTIME position.  WARNING: ENDIANNESS ISSUE HERE.
         */
        buf = apr_psprintf(r->pool, "%c%c%c%c%c%c%c%c%c%c", deflate_magic[0],
                           deflate_magic[1], Z_DEFLATED, 0 /* flags */,
                           0, 0, 0, 0 /* 4 chars for mtime */,
                           0 /* xflags */, OS_CODE);
        e = apr_bucket_pool_create(buf, 10, r->pool, f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(ctx->bb, e);

        /* If the entire Content-Encoding is "identity", we can replace it. */
        if (!encoding || !strcasecmp(encoding, "identity")) {
            apr_table_setn(r->headers_out, "Content-Encoding", "gzip");
        }
        else {
            apr_table_mergen(r->headers_out, "Content-Encoding", "gzip");
        }
        apr_table_unset(r->headers_out, "Content-Length");

        /* initialize deflate output buffer */
        ctx->stream.next_out = ctx->buffer;
        ctx->stream.avail_out = c->bufferSize;
    }
    
    while (!APR_BRIGADE_EMPTY(bb))
    {
        const char *data;
        apr_bucket *b;
        apr_size_t len;
        int done = 0;

        e = APR_BRIGADE_FIRST(bb);

        if (APR_BUCKET_IS_EOS(e)) {
            char *buf;
            unsigned int deflate_len;

            ctx->stream.avail_in = 0; /* should be zero already anyway */
            for (;;) {
                deflate_len = c->bufferSize - ctx->stream.avail_out;

                if (deflate_len != 0) {
                    b = apr_bucket_heap_create((char *)ctx->buffer,
                                               deflate_len, NULL,
                                               f->c->bucket_alloc);
                    APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
                    ctx->stream.next_out = ctx->buffer;
                    ctx->stream.avail_out = c->bufferSize;
                }

                if (done) {
                    break;
                }

                zRC = deflate(&ctx->stream, Z_FINISH);

                if (deflate_len == 0 && zRC == Z_BUF_ERROR) {
                    zRC = Z_OK;
                }

                done = (ctx->stream.avail_out != 0 || zRC == Z_STREAM_END);

                if (zRC != Z_OK && zRC != Z_STREAM_END) {
                    break;
                }
            }

            buf = apr_palloc(r->pool, 8);
            putLong((unsigned char *)&buf[0], ctx->crc);
            putLong((unsigned char *)&buf[4], ctx->stream.total_in);

            b = apr_bucket_pool_create(buf, 8, r->pool, f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "Zlib: Compressed %ld to %ld : URL %s",
                          ctx->stream.total_in, ctx->stream.total_out, r->uri);

            /* leave notes for logging */
            if (c->note_input_name) {
                apr_table_setn(r->notes, c->note_input_name,
                               (ctx->stream.total_in > 0)
                                ? apr_off_t_toa(r->pool,
                                                ctx->stream.total_in)
                                : "-");
            }

            if (c->note_output_name) {
                apr_table_setn(r->notes, c->note_output_name,
                               (ctx->stream.total_in > 0)
                                ? apr_off_t_toa(r->pool,
                                                ctx->stream.total_out)
                                : "-");
            }

            if (c->note_ratio_name) {
                apr_table_setn(r->notes, c->note_ratio_name,
                               (ctx->stream.total_in > 0)
                                ? apr_itoa(r->pool,
                                           (int)(ctx->stream.total_out
                                                 * 100
                                                 / ctx->stream.total_in))
                                : "-");
            }

            deflateEnd(&ctx->stream);

            /* Remove EOS from the old list, and insert into the new. */
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, e);

            /* Okay, we've seen the EOS.
             * Time to pass it along down the chain.
             */
            return ap_pass_brigade(f->next, ctx->bb);
        }

        if (APR_BUCKET_IS_FLUSH(e)) {
            apr_bucket *bkt;
            apr_status_t rv;

            apr_bucket_delete(e);

            if (ctx->stream.avail_in > 0) {
                zRC = deflate(&(ctx->stream), Z_SYNC_FLUSH);
                if (zRC != Z_OK) {
                    return APR_EGENERAL;
                }
            }

            ctx->stream.next_out = ctx->buffer;
            len = c->bufferSize - ctx->stream.avail_out;

            b = apr_bucket_heap_create((char *)ctx->buffer, len,
                                       NULL, f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
            ctx->stream.avail_out = c->bufferSize;

            bkt = apr_bucket_flush_create(f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, bkt);
            rv = ap_pass_brigade(f->next, ctx->bb);
            if (rv != APR_SUCCESS) {
                return rv;
            }
            continue;
        }

        /* read */
        apr_bucket_read(e, &data, &len, APR_BLOCK_READ);

        /* This crc32 function is from zlib. */
        ctx->crc = crc32(ctx->crc, (const Bytef *)data, len);

        /* write */
        ctx->stream.next_in = (unsigned char *)data; /* We just lost const-ness,
                                                      * but we'll just have to
                                                      * trust zlib */
        ctx->stream.avail_in = len;

        while (ctx->stream.avail_in != 0) {
            if (ctx->stream.avail_out == 0) {
                apr_status_t rv;

                ctx->stream.next_out = ctx->buffer;
                len = c->bufferSize - ctx->stream.avail_out;

                b = apr_bucket_heap_create((char *)ctx->buffer, len,
                                           NULL, f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
                ctx->stream.avail_out = c->bufferSize;
                /* Send what we have right now to the next filter. */
                rv = ap_pass_brigade(f->next, ctx->bb);
                if (rv != APR_SUCCESS) {
                    return rv;
                }
            }

            zRC = deflate(&(ctx->stream), Z_NO_FLUSH);

            if (zRC != Z_OK)
                return APR_EGENERAL;
        }

        apr_bucket_delete(e);
    }

    apr_brigade_cleanup(bb);
    return APR_SUCCESS;
}