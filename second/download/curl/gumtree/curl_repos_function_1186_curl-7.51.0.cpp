static void MD4_Update(MD4_CTX *ctx, const void *data, unsigned long size)
{
  MD4_u32plus saved_lo;
  unsigned long used, available;

  saved_lo = ctx->lo;
  if((ctx->lo = (saved_lo + size) & 0x1fffffff) < saved_lo)
    ctx->hi++;
  ctx->hi += (MD4_u32plus)size >> 29;

  used = saved_lo & 0x3f;

  if(used) {
    available = 64 - used;

    if(size < available) {
      memcpy(&ctx->buffer[used], data, size);
      return;
    }

    memcpy(&ctx->buffer[used], data, available);
    data = (const unsigned char *)data + available;
    size -= available;
    body(ctx, ctx->buffer, 64);
  }

  if(size >= 64) {
    data = body(ctx, data, size & ~(unsigned long)0x3f);
    size &= 0x3f;
  }

  memcpy(ctx->buffer, data, size);
}