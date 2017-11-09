static apr_status_t flush(brotli_ctx_t *ctx,
                          BrotliEncoderOperation op,
                          ap_filter_t *f)
{
    while (1) {
        const uint8_t *next_in = NULL;
        apr_size_t avail_in = 0;
        uint8_t *next_out = NULL;
        apr_size_t avail_out = 0;
        apr_size_t output_len;
        const uint8_t *output;
        apr_bucket *b;

        if (!BrotliEncoderCompressStream(ctx->state, op,
                                         &avail_in, &next_in,
                                         &avail_out, &next_out, NULL)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r, APLOGNO(03460)
                          "Error while compressing data");
            return APR_EGENERAL;
        }

        if (!BrotliEncoderHasMoreOutput(ctx->state)) {
            break;
        }

        /* A flush can require several calls to BrotliEncoderCompressStream(),
         * so place the data on the heap (otherwise, the pointer will become
         * invalid after the next call to BrotliEncoderCompressStream()).
         */
        output_len = 0;
        output = BrotliEncoderTakeOutput(ctx->state, &output_len);
        ctx->total_out += output_len;

        b = apr_bucket_heap_create((const char *)output, output_len, NULL,
                                   ctx->bb->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
    }

    return APR_SUCCESS;
}