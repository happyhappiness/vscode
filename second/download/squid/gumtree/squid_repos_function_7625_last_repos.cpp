size_t
base64_encode_final(struct base64_encode_ctx *ctx,
                    uint8_t *dst)
{
    unsigned done = 0;
    unsigned bits = ctx->bits;

    if (bits) {
        dst[done++] = ENCODE(ctx->word << (6 - ctx->bits));
        for (; bits < 6; bits += 2)
            dst[done++] = '=';

        ctx->bits = 0;
    }

    assert(done <= BASE64_ENCODE_FINAL_LENGTH);
    return done;
}