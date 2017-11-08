static int flush_libz_buffer(deflate_ctx *ctx, deflate_filter_config *c,
                             struct apr_bucket_alloc_t *bucket_alloc,
                             int (*libz_func)(z_streamp, int), int flush,
                             int crc)
{
    int zRC = Z_OK;
    int done = 0;
    unsigned int deflate_len;
    apr_bucket *b;

    for (;;) {
         deflate_len = c->bufferSize - ctx->stream.avail_out;

         if (deflate_len != 0) {
             /*
              * Do we need to update ctx->crc? Usually this is the case for
              * inflate action where we need to do a crc on the output, whereas
              * in the deflate case we need to do a crc on the input
              */
             if (crc) {
                 ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer,
                                  deflate_len);
             }
             b = apr_bucket_heap_create((char *)ctx->buffer,
                                        deflate_len, NULL,
                                        bucket_alloc);
             APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
             ctx->stream.next_out = ctx->buffer;
             ctx->stream.avail_out = c->bufferSize;
         }

         if (done)
             break;

         zRC = libz_func(&ctx->stream, flush);

         /*
          * We can ignore Z_BUF_ERROR because:
          * When we call libz_func we can assume that
          *
          * - avail_in is zero (due to the surrounding code that calls
          *   flush_libz_buffer)
          * - avail_out is non zero due to our actions some lines above
          *
          * So the only reason for Z_BUF_ERROR is that the internal libz
          * buffers are now empty and thus we called libz_func one time
          * too often. This does not hurt. It simply says that we are done.
          */
         if (zRC == Z_BUF_ERROR) {
             zRC = Z_OK;
             break;
         }

         done = (ctx->stream.avail_out != 0 || zRC == Z_STREAM_END);

         if (zRC != Z_OK && zRC != Z_STREAM_END)
             break;
    }
    return zRC;
}