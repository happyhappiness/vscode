        {
            const char *data;
            apr_size_t len;

            /* If we actually see the EOS, that means we screwed up! */
            if (APR_BUCKET_IS_EOS(bkt)) {
                inflateEnd(&ctx->stream);
                return APR_EGENERAL;
            }

            if (APR_BUCKET_IS_FLUSH(bkt)) {
                apr_bucket *tmp_heap;
                zRC = inflate(&(ctx->stream), Z_SYNC_FLUSH);
                if (zRC != Z_OK) {
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
                    return APR_EGENERAL;
                }
            }
            if (zRC == Z_STREAM_END) {
                apr_bucket *tmp_heap, *eos;

                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "Zlib: Inflated %ld to %ld : URL %s",
                              ctx->stream.total_in, ctx->stream.total_out,
                              r->uri);

