        }

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
                    return APR_EGENERAL;
                }
                ctx->stream.next_in += 4;
                compLen = getLong(ctx->stream.next_in);
                if (ctx->stream.total_out != compLen) {
                    inflateEnd(&ctx->stream);
                    return APR_EGENERAL;
                }
            }
            else {
                /* FIXME: We need to grab the 8 verification bytes
                 * from the wire! */
                inflateEnd(&ctx->stream);
                return APR_EGENERAL;
            }

            inflateEnd(&ctx->stream);

            eos = apr_bucket_eos_create(f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, eos);
            break;
        }

    }

    rv = ap_pass_brigade(f->next, ctx->proc_bb);
    apr_brigade_cleanup(ctx->proc_bb);
    return rv ;
}

static void register_hooks(apr_pool_t *p)
{
    ap_register_output_filter(deflateFilterName, deflate_out_filter, NULL,
                              AP_FTYPE_CONTENT_SET);
    ap_register_output_filter("INFLATE", inflate_out_filter, NULL,
                              AP_FTYPE_RESOURCE-1);
