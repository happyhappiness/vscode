size_t
base64_encode_single(struct base64_encode_ctx *ctx,
                     uint8_t *dst,
                     uint8_t src)
{
    unsigned done = 0;
    unsigned word = ctx->word << 8 | src;
    unsigned bits = ctx->bits + 8;

    while (bits >= 6) {
        bits -= 6;
        dst[done++] = ENCODE(word >> bits);
    }

    ctx->bits = bits;
    ctx->word = word;

    assert(done <= 2);

    return done;
}