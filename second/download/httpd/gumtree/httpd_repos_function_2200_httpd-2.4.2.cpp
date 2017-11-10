static apr_status_t deflate_in_filter(ap_filter_t *f,
                                      apr_bucket_brigade *bb,
                                      ap_input_mode_t mode,
                                      apr_read_type_e block,
                                      apr_off_t readbytes)
{
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
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01387) "Zlib: Invalid header");
            return APR_EGENERAL;
        }

        /* We can't handle flags for now. */
        if (deflate_hdr[3] != 0) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01388)
                          "Zlib: Unsupported flags %02x", (int)deflate_hdr[3]);
            return APR_EGENERAL;
        }

        zRC = inflateInit2(&ctx->stream, c->windowSize);

        if (zRC != Z_OK) {
            f->ctx = NULL;
            inflateEnd(&ctx->stream);
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01389)
                          "unable to init Zlib: "
                          "inflateInit2 returned %d: URL %s",
                          zRC, r->uri);
            ap_remove_input_filter(f);
            return ap_get_brigade(f->next, bb, mode, block, readbytes);
        }

        /* initialize deflate output buffer */
        ctx->stream.next_out = ctx->buffer;
        ctx->stream.avail_out = c->bufferSize;

        apr_brigade_cleanup(ctx->bb);
    }

    if (APR_BRIGADE_EMPTY(ctx->proc_bb)) {
        rv = ap_get_brigade(f->next, ctx->bb, mode, block, readbytes);

        if (rv != APR_SUCCESS) {
            /* What about APR_EAGAIN errors? */
            inflateEnd(&ctx->stream);
            return rv;
        }

        for (bkt = APR_BRIGADE_FIRST(ctx->bb);
             bkt != APR_BRIGADE_SENTINEL(ctx->bb);
             bkt = APR_BUCKET_NEXT(bkt))
        {
            const char *data;
            apr_size_t len;

            /* If we actually see the EOS, that means we screwed up! */
            if (APR_BUCKET_IS_EOS(bkt)) {
                inflateEnd(&ctx->stream);
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01390)
                              "Encountered EOS bucket in inflate filter (bug?)");
                return APR_EGENERAL;
            }

            if (APR_BUCKET_IS_FLUSH(bkt)) {
                apr_bucket *tmp_heap;
                zRC = inflate(&(ctx->stream), Z_SYNC_FLUSH);
                if (zRC != Z_OK) {
                    inflateEnd(&ctx->stream);
                    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01391)
                                  "Zlib error %d inflating data (%s)", zRC,
                                  ctx->stream.msg);
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
                APR_BRIGADE_CONCAT(bb, ctx->bb);
                break;
            }

            /* read */
            apr_bucket_read(bkt, &data, &len, APR_BLOCK_READ);

            /* pass through zlib inflate. */
            ctx->stream.next_in = (unsigned char *)data;
            ctx->stream.avail_in = len;

            zRC = Z_OK;

            while (ctx->stream.avail_in != 0) {
                if (ctx->stream.avail_out == 0) {
                    apr_bucket *tmp_heap;
                    ctx->stream.next_out = ctx->buffer;
                    len = c->bufferSize - ctx->stream.avail_out;

                    ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
                    tmp_heap = apr_bucket_heap_create((char *)ctx->buffer, len,
                                                      NULL, f->c->bucket_alloc);
                    APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_heap);
                    ctx->stream.avail_out = c->bufferSize;
                }

                zRC = inflate(&ctx->stream, Z_NO_FLUSH);

                if (zRC == Z_STREAM_END) {
                    break;
                }

                if (zRC != Z_OK) {
                    inflateEnd(&ctx->stream);
                    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01392)
                                  "Zlib error %d inflating data (%s)", zRC,
                                  ctx->stream.msg);
                    return APR_EGENERAL;
                }
            }
            if (zRC == Z_STREAM_END) {
                apr_bucket *tmp_heap, *eos;

                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01393)
                              "Zlib: Inflated %ld to %ld : URL %s",
                              ctx->stream.total_in, ctx->stream.total_out,
                              r->uri);

                len = c->bufferSize - ctx->stream.avail_out;

                ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
                tmp_heap = apr_bucket_heap_create((char *)ctx->buffer, len,
                                                  NULL, f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_heap);
                ctx->stream.avail_out = c->bufferSize;

                /* Is the remaining 8 bytes already in the avail stream? */
                if (ctx->stream.avail_in >= 8) {
                    unsigned long compCRC, compLen;
                    compCRC = getLong(ctx->stream.next_in);
                    if (ctx->crc != compCRC) {
                        inflateEnd(&ctx->stream);
                        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01394)
                                 