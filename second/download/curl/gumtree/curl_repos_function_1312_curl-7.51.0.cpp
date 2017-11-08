static void MD5_Final(unsigned char *result, MD5_CTX *ctx)
{
  unsigned long used, available;

  used = ctx->lo & 0x3f;

  ctx->buffer[used++] = 0x80;

  available = 64 - used;

  if(available < 8) {
    memset(&ctx->buffer[used], 0, available);
    body(ctx, ctx->buffer, 64);
    used = 0;
    available = 64;
  }

  memset(&ctx->buffer[used], 0, available - 8);

  ctx->lo <<= 3;
  ctx->buffer[56] = curlx_ultouc((ctx->lo)&0xff);
  ctx->buffer[57] = curlx_ultouc((ctx->lo >> 8)&0xff);
  ctx->buffer[58] = curlx_ultouc((ctx->lo >> 16)&0xff);
  ctx->buffer[59] = curlx_ultouc(ctx->lo >> 24);
  ctx->buffer[60] = curlx_ultouc((ctx->hi)&0xff);
  ctx->buffer[61] = curlx_ultouc((ctx->hi >> 8)&0xff);
  ctx->buffer[62] = curlx_ultouc((ctx->hi >> 16)&0xff);
  ctx->buffer[63] = curlx_ultouc(ctx->hi >> 24);

  body(ctx, ctx->buffer, 64);

  result[0] = curlx_ultouc((ctx->a)&0xff);
  result[1] = curlx_ultouc((ctx->a >> 8)&0xff);
  result[2] = curlx_ultouc((ctx->a >> 16)&0xff);
  result[3] = curlx_ultouc(ctx->a >> 24);
  result[4] = curlx_ultouc((ctx->b)&0xff);
  result[5] = curlx_ultouc((ctx->b >> 8)&0xff);
  result[6] = curlx_ultouc((ctx->b >> 16)&0xff);
  result[7] = curlx_ultouc(ctx->b >> 24);
  result[8] = curlx_ultouc((ctx->c)&0xff);
  result[9] = curlx_ultouc((ctx->c >> 8)&0xff);
  result[10] = curlx_ultouc((ctx->c >> 16)&0xff);
  result[11] = curlx_ultouc(ctx->c >> 24);
  result[12] = curlx_ultouc((ctx->d)&0xff);
  result[13] = curlx_ultouc((ctx->d >> 8)&0xff);
  result[14] = curlx_ultouc((ctx->d >> 16)&0xff);
  result[15] = curlx_ultouc(ctx->d >> 24);

  memset(ctx, 0, sizeof(*ctx));
}