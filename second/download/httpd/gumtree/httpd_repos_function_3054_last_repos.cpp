static apr_status_t process_chunk(brotli_ctx_t *ctx,
                                  const void *data,
                                  apr_size_t len,
                                  ap_filter_t *f)
{
    const uint8_t *next_in = data;
    apr_size_t avail_in = len;

    while (avail_in > 0) {
        uint8_t *next_out = NULL;
        apr_size_t avail_out = 0;

        if (!BrotliEncoderCompressStream(ctx->state,
                                         BROTLI_OPERATION_PROCESS,
                                         &avail_in, &next_in,
                                         &avail_out, &next_out, NULL)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r, APLOGNO(03459)
                          "Error while compressing data");
            return APR_EGENERAL;
        }

        if (BrotliEncoderHasMoreOutput(ctx->state)) {
            apr_size_t output_len = 0;
            const uint8_t *output;
            apr_status_t rv;
            apr_bucket *b;

            /* Drain the accumulated output.  Avoid copying the data by
             * wrapping a pointer to the internal output buffer and passing
             * it down to the next filter.  The pointer is only valid until
             * the next call to BrotliEncoderCompressStream(), but we're okay
             * with that, since the brigade is cleaned up right after the
             * ap_pass_brigade() call.
             */
            output = BrotliEncoderTakeOutput(ctx->state, &output_len);
            ctx->total_out += output_len;

            b = apr_bucket_transient_create((const char *)output, output_len,
                                            ctx->bb->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, b);

            rv = ap_pass_brigade(f->next, ctx->bb);
            apr_brigade_cleanup(ctx->bb);
            if (rv != APR_SUCCESS) {
                return rv;
            }
        }
    }

    ctx->total_in += len;
    return APR_SUCCESS;
}