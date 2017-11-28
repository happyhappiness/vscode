int
base64_decode_update(struct base64_decode_ctx *ctx,
                     size_t *dst_length,
                     uint8_t *dst,
                     size_t src_length,
                     const uint8_t *src)
{
    size_t done;
    size_t i;

    for (i = 0, done = 0; i < src_length; i++) {
        switch(base64_decode_single(ctx, dst + done, src[i])) {
        case -1:
            return 0;
        case 1:
            done++;
        /* Fall through */
        case 0:
            break;
        default:
            abort();
        }
    }

    assert(done <= BASE64_DECODE_LENGTH(src_length));

    *dst_length = done;
    return 1;
}