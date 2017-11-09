static apr_status_t compress_filter(ap_filter_t *f, apr_bucket_brigade *bb)
{
    request_rec *r = f->r;
    brotli_ctx_t *ctx = f->ctx;
    apr_status_t rv;
    brotli_server_config_t *conf;

    if (APR_BRIGADE_EMPTY(bb)) {
        return APR_SUCCESS;
    }

    conf = ap_get_module_config(r->server->module_config, &brotli_module);

    if (!ctx) {
        const char *encoding;
        const char *token;
        const char *accepts;

        /* Only work on main request, not subrequests, that are not
         * a 204 response with no content, and are not tagged with the
         * no-brotli env variable, and are not a partial response to
         * a Range request.
         */
        if (r->main || r->status == HTTP_NO_CONTENT
            || apr_table_get(r->subprocess_env, "no-brotli")
            || apr_table_get(r->headers_out, "Content-Range")) {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        /* Let's see what our current Content-Encoding is. */
        encoding = get_content_encoding(r);

        if (encoding) {
            const char *tmp = encoding;

            token = ap_get_token(r->pool, &tmp, 0);
            while (token && *token) {
                if (strcmp(token, "identity") != 0 &&
                    strcmp(token, "7bit") != 0 &&
                    strcmp(token, "8bit") != 0 &&
                    strcmp(token, "binary") != 0) {
                    /* The data is already encoded, do nothing. */
                    ap_remove_output_filter(f);
                    return ap_pass_brigade(f->next, bb);
                }

                if (*tmp) {
                    ++tmp;
                }
                token = (*tmp) ? ap_get_token(r->pool, &tmp, 0) : NULL;
            }
        }

        /* Even if we don't accept this request based on it not having
         * the Accept-Encoding, we need to note that we were looking
         * for this header and downstream proxies should be aware of
         * that.
         */
        apr_table_mergen(r->headers_out, "Vary", "Accept-Encoding");

        accepts = apr_table_get(r->headers_in, "Accept-Encoding");
        if (!accepts) {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        /* Do we have Accept-Encoding: br? */
        token = ap_get_token(r->pool, &accepts, 0);
        while (token && token[0] && ap_cstr_casecmp(token, "br") != 0) {
            while (*accepts == ';') {
                ++accepts;
                ap_get_token(r->pool, &accepts, 1);
            }

            if (*accepts == ',') {
                ++accepts;
            }
            token = (*accepts) ? ap_get_token(r->pool, &accepts, 0) : NULL;
        }

        if (!token || token[0] == '\0') {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        /* If the entire Content-Encoding is "identity", we can replace it. */
        if (!encoding || ap_cstr_casecmp(encoding, "identity") == 0) {
            apr_table_setn(r->headers_out, "Content-Encoding", "br");
        } else {
            apr_table_mergen(r->headers_out, "Content-Encoding", "br");
        }

        if (r->content_encoding) {
            r->content_encoding = apr_table_get(r->headers_out,
                                                "Content-Encoding");
        }

        apr_table_unset(r->headers_out, "Content-Length");
        apr_table_unset(r->headers_out, "Content-MD5");

        /* https://bz.apache.org/bugzilla/show_bug.cgi?id=39727
         * https://bz.apache.org/bugzilla/show_bug.cgi?id=45023
         *
         * ETag must be unique among the possible representations, so a
         * change to content-encoding requires a corresponding change to the
         * ETag.  We make this behavior configurable, and mimic mod_deflate's
         * DeflateAlterETag with BrotliAlterETag to keep the transition from
         * mod_deflate seamless.
         */
        if (conf->etag_mode == ETAG_MODE_REMOVE) {
            apr_table_unset(r->headers_out, "ETag");
        }
        else if (conf->etag_mode == ETAG_MODE_ADDSUFFIX) {
            const char *etag = apr_table_get(r->headers_out, "ETag");

            if (etag) {
                apr_size_t len = strlen(etag);

                if (len > 2 && etag[len - 1] == '"') {
                    etag = apr_pstrmemdup(r->pool, etag, len - 1);
                    etag = apr_pstrcat(r->pool, etag, "-br\"", NULL);
                    apr_table_setn(r->headers_out, "ETag", etag);
                }
            }
        }

        /* For 304 responses, we only need to send out the headers. */
        if (r->status == HTTP_NOT_MODIFIED) {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        ctx = create_ctx(conf->quality, conf->lgwin, conf->lgblock,
                         f->c->bucket_alloc, r->pool);
        f->ctx = ctx;
    }

    while (!APR_BRIGADE_EMPTY(bb)) {
        apr_bucket *e = APR_BRIGADE_FIRST(bb);

        /* Optimization: If we are a HEAD request and bytes_sent is not zero
         * it means that we have passed the content-length filter once and
         * have more data to send.  This means that the content-length filter
         * could not determine our content-length for the response to the
         * HEAD request anyway (the associated GET request would deliver the
         * body in chunked encoding) and we can stop compressing.
         */
        if (r->header_only && r->bytes_sent) {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        if (APR_BUCKET_IS_EOS(e)) {
            rv = flush(ctx, BROTLI_OPERATION_FINISH, f);
            if (rv != APR_SUCCESS) {
                return rv;
            }

            /* Leave notes for logging. */
            if (conf->note_input_name) {
                apr_table_setn(r->notes, conf->note_input_name,
                               apr_off_t_toa(r->pool, ctx->total_in));
            }
            if (conf->note_output_name) {
                apr_table_setn(r->notes, conf->note_output_name,
                               apr_off_t_toa(r->pool, ctx->total_out));
            }
            if (conf->note_ratio_name) {
                if (ctx->total_in > 0) {
                    int ratio = (int) (ctx->total_out * 100 / ctx->total_in);

                    apr_table_setn(r->notes, conf->note_ratio_name,
                                   apr_itoa(r->pool, ratio));
                }
                else {
                    apr_table_setn(r->notes, conf->note_ratio_name, "-");
                }
            }

            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, e);

            rv = ap_pass_brigade(f->next, ctx->bb);
            apr_brigade_cleanup(ctx->bb);
            apr_pool_cleanup_run(r->pool, ctx, cleanup_ctx);
            return rv;
        }
        else if (APR_BUCKET_IS_FLUSH(e)) {
            rv = flush(ctx, BROTLI_OPERATION_FLUSH, f);
            if (rv != APR_SUCCESS) {
                return rv;
            }

            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, e);

            rv = ap_pass_brigade(f->next, ctx->bb);
            apr_brigade_cleanup(ctx->bb);
            if (rv != APR_SUCCESS) {
                return rv;
            }
        }
        else if (APR_BUCKET_IS_METADATA(e)) {
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, e);
        }
        else {
            const char *data;
            apr_size_t len;

            rv = apr_bucket_read(e, &data, &len, APR_BLOCK_READ);
            if (rv != APR_SUCCESS) {
                return rv;
            }
            rv = process_chunk(ctx, data, len, f);
            if (rv != APR_SUCCESS) {
                return rv;
            }
            apr_bucket_delete(e);
        }
    }
    return APR_SUCCESS;
}