void
SquidMD5Update(struct SquidMD5Context *ctx, const void *_buf, unsigned len)
{
    uint8_t const *buf = _buf;
    uint32_t t;

    /* Update byte count */

    t = ctx->bytes[0];
    if ((ctx->bytes[0] = t + len) < t)
        ctx->bytes[1]++;    /* Carry from low to high */

    t = 64 - (t & 0x3f);    /* Space available in ctx->in (at least 1) */
    if (t > len) {
        memcpy((uint8_t *) ctx->in + 64 - t, buf, len);
        return;
    }
    /* First chunk is an odd size */
    memcpy((uint8_t *) ctx->in + 64 - t, buf, t);
    byteSwap(ctx->in, 16);
    SquidMD5Transform(ctx->buf, ctx->in);
    buf += t;
    len -= t;

    /* Process data in 64-byte chunks */
    while (len >= 64) {
        memcpy(ctx->in, buf, 64);
        byteSwap(ctx->in, 16);
        SquidMD5Transform(ctx->buf, ctx->in);
        buf += 64;
        len -= 64;
    }

    /* Handle any remaining bytes of data. */
    memcpy(ctx->in, buf, len);
}