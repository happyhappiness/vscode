        {
            const char *data;
            apr_size_t len;

            /* If we actually see the EOS, that means we screwed up! */
            if (APR_BUCKET_IS_EOS(bkt)) {
                if (!ctx->done) {
                    inflateEnd(&ctx->stream);
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Encountered premature end-of-stream while inflating");
                    return APR_EGENERAL;
                }

                /* Move everything to the returning brigade. */
                APR_BUCKET_REMOVE(bkt);
                APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, bkt);
                break;
            }

            if (APR_BUCKET_IS_FLUSH(bkt)) {
                apr_bucket *tmp_b;
                zRC = inflate(&(ctx->stream), Z_SYNC_FLUSH);
                if (zRC != Z_OK) {
                    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                                  "Zlib error %d inflating data (%s)", zRC,
                                  ctx->stream.msg);
                    inflateEnd(&ctx->stream);
                    return APR_EGENERAL;
                }

                ctx->stream.next_out = ctx->buffer;
                len = c->bufferSize - ctx->stream.avail_out;
 
                ctx->inflate_total += len;
                if (inflate_limit && ctx->inflate_total > inflate_limit) { 
                    inflateEnd(&ctx->stream);
                    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, 
                            "Inflated content length of %" APR_OFF_T_FMT
                            " is larger than the configured limit"
                            " of %" APR_OFF_T_FMT, 
                            ctx->inflate_total, inflate_limit);
                    return APR_ENOSPC;
                }

                ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
                tmp_b = apr_bucket_heap_create((char *)ctx->buffer, len,
                                                NULL, f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_b);
                ctx->stream.avail_out = c->bufferSize;

                /* Flush everything so far in the returning brigade, but continue
                 * reading should EOS/more follow (don't lose them).
                 */
                tmp_b = APR_BUCKET_PREV(bkt);
                APR_BUCKET_REMOVE(bkt);
                APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, bkt);
                bkt = tmp_b;
                continue;
            }

            /* sanity check - data after completed compressed body and before eos? */
            if (ctx->done) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Encountered extra data after compressed data");
                return APR_EGENERAL;
            }

            /* read */
            apr_bucket_read(bkt, &data, &len, APR_BLOCK_READ);
            if (!len) {
                continue;
            }
            if (len > APR_INT32_MAX) {
                apr_bucket_split(bkt, APR_INT32_MAX);
                apr_bucket_read(bkt, &data, &len, APR_BLOCK_READ);
            }

            if (ctx->zlib_flags) {
                rv = consume_zlib_flags(ctx, &data, &len);
                if (rv == APR_SUCCESS) {
                    ctx->zlib_flags = 0;
                }
                if (!len) {
                    continue;
                }
            }

            /* pass through zlib inflate. */
            ctx->stream.next_in = (unsigned char *)data;
            ctx->stream.avail_in = (int)len;

            zRC = Z_OK;

            if (!ctx->validation_buffer) {
                while (ctx->stream.avail_in != 0) {
                    if (ctx->stream.avail_out == 0) {
                        apr_bucket *tmp_heap;
                        ctx->stream.next_out = ctx->buffer;
                        len = c->bufferSize - ctx->stream.avail_out;

                        ctx->inflate_total += len;
                        if (inflate_limit && ctx->inflate_total > inflate_limit) { 
                            inflateEnd(&ctx->stream);
                            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                                    "Inflated content length of %" APR_OFF_T_FMT
                                    " is larger than the configured limit"
                                    " of %" APR_OFF_T_FMT, 
                                    ctx->inflate_total, inflate_limit);
                            return APR_ENOSPC;
                        }

                        if (!check_ratio(r, ctx, dc)) {
                            inflateEnd(&ctx->stream);
                            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, 
                                    "Inflated content ratio is larger than the "
                                    "configured limit %i by %i time(s)",
                                    dc->ratio_limit, dc->ratio_burst);
                            return APR_EINVAL;
                        }

                        ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
                        tmp_heap = apr_bucket_heap_create((char *)ctx->buffer, len,
                                                          NULL, f->c->bucket_alloc);
                        APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_heap);
                        ctx->stream.avail_out = c->bufferSize;
                    }

                    zRC = inflate(&ctx->stream, Z_NO_FLUSH);

                    if (zRC == Z_STREAM_END) {
                        ctx->validation_buffer = apr_pcalloc(r->pool,
                                                             VALIDATION_SIZE);
                        ctx->validation_buffer_length = 0;
                        break;
                    }

                    if (zRC != Z_OK) {
                        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                                      "Zlib error %d inflating data (%s)", zRC,
                                      ctx->stream.msg);
                        inflateEnd(&ctx->stream);
                        return APR_EGENERAL;
                    }
                }
            }

            if (ctx->validation_buffer) {
                apr_bucket *tmp_heap;
                apr_size_t avail, valid;
                unsigned char *buf = ctx->validation_buffer;

                avail = ctx->stream.avail_in;
                valid = (apr_size_t)VALIDATION_SIZE -
                         ctx->validation_buffer_length;

                /*
                 * We have inflated all data. Now try to capture the
                 * validation bytes. We may not have them all available
                 * right now, but capture what is there.
                 */
                if (avail < valid) {
                    memcpy(buf + ctx->validation_buffer_length,
                           ctx->stream.next_in, avail);
                    ctx->validation_buffer_length += avail;
                    continue;
                }
                memcpy(buf + ctx->validation_buffer_length,
                       ctx->stream.next_in, valid);
                ctx->validation_buffer_length += valid;

                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "Zlib: Inflated %ld to %ld : URL %s",
                              ctx->stream.total_in, ctx->stream.total_out,
                              r->uri);

