void *
md5_finish_ctx (struct md5_ctx *ctx, void *resbuf)
{
  /* Take yet unprocessed bytes into account.  */
  md5_uint32 bytes = ctx->buflen;
  size_t size = (bytes < 56) ? 64 / 4 : 64 * 2 / 4;

  /* Now count remaining bytes.  */
  ctx->total[0] += bytes;
  if (ctx->total[0] < bytes)
    ++ctx->total[1];

  /* Put the 64-bit file length in *bits* at the end of the buffer.  */
  ctx->buffer[size - 2] = SWAP (ctx->total[0] << 3);
  ctx->buffer[size - 1] = SWAP ((ctx->total[1] << 3) | (ctx->total[0] >> 29));

  memcpy (&((char *) ctx->buffer)[bytes], fillbuf, (size - 2) * 4 - bytes);

  /* Process last bytes.  */
  md5_process_block (ctx->buffer, size * 4, ctx);

  return md5_read_ctx (ctx, resbuf);
}