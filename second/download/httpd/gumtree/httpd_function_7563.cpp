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
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02619)
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
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01387)
                          "Zlib: Invalid header");
            return APR_EGENERAL;
        }

        ctx->zlib_flags = ctx->header[3];
        if ((ctx->zlib_flags & RESERVED)) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01388)
                          "Zlib: Invalid flags %02x", ctx->zlib_flags);
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

    inflate_limit = dc->inflate_limit; 
    if (inflate_limit == 0) { 
        /* The core is checking the deflated body, we'll check the inflated */
        inflate_limit = ap_get_limit_req_body(f->r);
    }

    if (APR_BRIGADE_EMPTY(ctx->proc_bb)) {
        rv = ap_get_brigade(f->next, ctx->bb, mode, block, readbytes);

        /* Don't terminate on EAGAIN (or success with an empty brigade in
         * non-blocking mode), just return focus.
         */
        if (block == APR_NONBLOCK_READ
                && (APR_STATUS_IS_EAGAIN(rv)
                    || (rv == APR_SUCCESS && APR_BRIGADE_EMPTY(ctx->bb)))) {
            return rv;
        }
        if (rv != APR_SUCCESS) {
            inflateEnd(&ctx->stream);
            return rv;
        }

        for (bkt = APR_BRIGADE_FIRST(ctx->bb);
             bkt != APR_BRIGADE_SENTINEL(ctx->bb);
             bkt = APR_BUCKET_NEXT(bkt))
        {
            const char *data;
            apr_size_t len;

            if (APR_BUCKET_IS_EOS(bkt)) {
                if (!ctx->done) {
                    inflateEnd(&ctx->stream);
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02481)
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
                    inflateEnd(&ctx->stream);
                    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01391)
                                  "Zlib error %d inflating data (%s)", zRC,
                                  ctx->stream.msg);
                    return APR_EGENERAL;
                }

                ctx->stream.next_out = ctx->buffer;
                len = c->bufferSize - ctx->stream.avail_out;
 
                ctx->inflate_total += len;
                if (inflate_limit && ctx->inflate_total > inflate_limit) { 
                    inflateEnd(&ctx->stream);
                    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02647)
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
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02482)
                              "Encountered extra data after compressed data");
                return APR_EGENERAL;
            }

            /* read */
            apr_bucket_read(bkt, &data, &len, APR_BLOCK_READ);
            if (!len) {
                continue;
            }
            if (len > INT_MAX) {
                apr_bucket_split(bkt, INT_MAX);
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
                            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02648)
                                    "Inflated content length of %" APR_OFF_T_FMT
                                    " is larger than the configured limit"
                                    " of %" APR_OFF_T_FMT, 
                                    ctx->inflate_total, inflate_limit);
                            return APR_ENOSPC;
                        }

                        if (!check_ratio(r, ctx, dc)) {
                            inflateEnd(&ctx->stream);
                            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02649)
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
                        inflateEnd(&ctx->stream);
                        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01392)
                                      "Zlib error %d inflating data (%s)", zRC,
                                      ctx->stream.msg);
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

                {
                    unsigned long compCRC, compLen;
                    compCRC = getLong(buf);
                    if (ctx->crc != compCRC) {
                        inflateEnd(&ctx->stream);
                        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01394)
                                      "Zlib: CRC error inflating data");
                        return APR_EGENERAL;
                    }
                    compLen = getLong(buf + VALIDATION_SIZE / 2);
                    /* gzip stores original size only as 4 byte value */
                    if ((ctx->stream.total_out & 0xFFFFFFFF) != compLen) {
                        inflateEnd(&ctx->stream);
                        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01395)
                                      "Zlib: Length %ld of inflated data does "
                                      "not match expected value %ld",
                                      ctx->stream.total_out, compLen);
                        return APR_EGENERAL;
                    }
                }

                inflateEnd(&ctx->stream);

                ctx->done = 1;

                /* Did we have trailing data behind the closing 8 bytes? */
                if (avail > valid) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02485)
                                  "Encountered extra data after compressed data");
                    return APR_EGENERAL;
                }
            }

        }
        apr_brigade_cleanup(ctx->bb);
    }

    /* If we are about to return nothing for a 'blocking' read and we have
     * some data in our zlib buffer, flush it out so we can return something.
     */
    if (block == APR_BLOCK_READ &&
            APR_BRIGADE_EMPTY(ctx->proc_bb) &&
            ctx->stream.avail_out < c->bufferSize) {
        apr_bucket *tmp_heap;
        apr_size_t len;
        ctx->stream.next_out = ctx->buffer;
        len = c->bufferSize - ctx->stream.avail_out;

        ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
        tmp_heap = apr_bucket_heap_create((char *)ctx->buffer, len,
                                          NULL, f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_heap);
        ctx->stream.avail_out = c->bufferSize;
    }

    if (!APR_BRIGADE_EMPTY(ctx->proc_bb)) {
        if (apr_brigade_partition(ctx->proc_bb, readbytes, &bkt) == APR_INCOMPLETE) {
            APR_BRIGADE_CONCAT(bb, ctx->proc_bb);
        }
        else {
            APR_BRIGADE_CONCAT(bb, ctx->proc_bb);
            apr_brigade_split_ex(bb, bkt, ctx->proc_bb);
        }
        if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(bb))) {
            ap_remove_input_filter(f);
        }
    }

    return APR_SUCCESS;
}