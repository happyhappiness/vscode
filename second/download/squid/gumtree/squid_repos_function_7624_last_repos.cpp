size_t
base64_encode_update(struct base64_encode_ctx *ctx,
                     uint8_t *dst,
                     size_t length,
                     const uint8_t *src)
{
    size_t done = 0;
    size_t left = length;
    unsigned left_over;
    size_t bulk;

    while (ctx->bits && left) {
        left--;
        done += base64_encode_single(ctx, dst + done, *src++);
    }

    left_over = left % 3;
    bulk = left - left_over;

    if (bulk) {
        assert(!(bulk % 3));

        base64_encode_raw(dst + done, bulk, src);
        done += BASE64_ENCODE_RAW_LENGTH(bulk);
        src += bulk;
        left = left_over;
    }

    while (left) {
        left--;
        done += base64_encode_single(ctx, dst + done, *src++);
    }

    assert(done <= BASE64_ENCODE_LENGTH(length));

    return done;
}