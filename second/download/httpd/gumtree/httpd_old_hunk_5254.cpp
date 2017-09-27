        if (APR_BUCKET_IS_FLUSH(e)) {
            apr_status_t rv;

            /* flush the remaining data from the zlib buffers */
            zRC = flush_libz_buffer(ctx, c, f->c->bucket_alloc, inflate,
                                    Z_SYNC_FLUSH, UPDATE_CRC);
            if (zRC != Z_OK) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01402)
                              "Zlib error %d flushing inflate buffer (%s)",
                              zRC, ctx->stream.msg);
                return APR_EGENERAL;
            }

