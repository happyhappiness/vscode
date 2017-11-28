static int
base64_decode_single(struct base64_decode_ctx *ctx, uint8_t *dst, uint8_t src)
{
    int data = decode_table[src];

    switch(data) {
    default:
        assert(data >= 0 && data < 0x40);

        if (ctx->padding)
            return -1;

        ctx->word = ctx->word << 6 | data;
        ctx->bits += 6;

        if (ctx->bits >= 8) {
            ctx->bits -= 8;
            dst[0] = ctx->word >> ctx->bits;
            return 1;
        } else
            return 0;

    case TABLE_INVALID:
        return -1;

    case TABLE_SPACE:
        return 0;

    case TABLE_END:
        /* There can be at most two padding characters. */
        if (!ctx->bits || ctx->padding > 2)
            return -1;

        if (ctx->word & ( (1<<ctx->bits) - 1))
            /* We shouldn't have any leftover bits */
            return -1;

        ctx->padding++;
        ctx->bits -= 2;
        return 0;
    }
}