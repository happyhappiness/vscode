            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }


        f->ctx = ctx = apr_pcalloc(f->r->pool, sizeof(*ctx));
        ctx->proc_bb = apr_brigade_create(r->pool, f->c->bucket_alloc);
        ctx->buffer = apr_palloc(r->pool, c->bufferSize);


        zRC = inflateInit2(&ctx->stream, c->windowSize);

        if (zRC != Z_OK) {
            f->ctx = NULL;
            inflateEnd(&ctx->stream);
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "unable to init Zlib: "
                          "inflateInit2 returned %d: URL %s",
                          zRC, r->uri);
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        /* initialize deflate output buffer */
        ctx->stream.next_out = ctx->buffer;
        ctx->stream.avail_out = c->bufferSize;

        deflate_init = 0;
    }

    for (bkt = APR_BRIGADE_FIRST(bb);
         bkt != APR_BRIGADE_SENTINEL(bb);
         bkt = APR_BUCKET_NEXT(bkt))
    {
        const char *data;
        apr_size_t len;

        /* If we actually see the EOS, that means we screwed up! */
        /* no it doesn't - not in a HEAD or 204/304 */
        if (APR_BUCKET_IS_EOS(bkt)) {
            inflateEnd(&ctx->stream);
            return ap_pass_brigade(f->next, bb);
        }

        if (APR_BUCKET_IS_FLUSH(bkt)) {
            apr_bucket *tmp_heap;
            zRC = inflate(&(ctx->stream), Z_SYNC_FLUSH);
            if (zRC != Z_OK) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Inflate error %d on flush", zRC);
                inflateEnd(&ctx->stream);
                return APR_EGENERAL;
            }

            ctx->stream.next_out = ctx->buffer;
            len = c->bufferSize - ctx->stream.avail_out;

            ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
            tmp_heap = apr_bucket_heap_create((char *)ctx->buffer, len,
                                             NULL, f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_heap);
            ctx->stream.avail_out = c->bufferSize;

            /* Move everything to the returning brigade. */
            APR_BUCKET_REMOVE(bkt);
            break;
        }

        /* read */
        apr_bucket_read(bkt, &data, &len, APR_BLOCK_READ);

        /* first bucket contains zlib header */
        if (!deflate_init++) {
            if (len < 10) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Insufficient data for inflate");
                return APR_EGENERAL;
            }
            else  {
