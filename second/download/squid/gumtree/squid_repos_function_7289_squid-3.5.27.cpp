void
SquidMD5Final(unsigned char digest[16], struct SquidMD5Context *ctx)
{
    int count = ctx->bytes[0] & 0x3f;   /* Number of bytes in ctx->in */
    uint8_t *p = (uint8_t *) ctx->in + count;

    /* Set the first char of padding to 0x80.  There is always room. */
    *p++ = 0x80;

    /* Bytes of padding needed to make 56 bytes (-8..55) */
    count = 56 - 1 - count;

    if (count < 0) {        /* Padding forces an extra block */
        memset(p, 0, count + 8);
        byteSwap(ctx->in, 16);
        SquidMD5Transform(ctx->buf, ctx->in);
        p = (uint8_t *) ctx->in;
        count = 56;
    }
    memset(p, 0, count);
    byteSwap(ctx->in, 14);

    /* Append length in bits and transform */
    ctx->in[14] = ctx->bytes[0] << 3;
    ctx->in[15] = ctx->bytes[1] << 3 | ctx->bytes[0] >> 29;
    SquidMD5Transform(ctx->buf, ctx->in);

    byteSwap(ctx->buf, 4);
    memcpy(digest, ctx->buf, 16);
    memset(ctx, 0, sizeof(*ctx));   /* In case it's sensitive */
}