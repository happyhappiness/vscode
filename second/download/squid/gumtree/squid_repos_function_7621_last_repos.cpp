static void
base64_encode_raw(uint8_t *dst, size_t length, const uint8_t *src)
{
    const uint8_t *in = src + length;
    uint8_t *out = dst + BASE64_ENCODE_RAW_LENGTH(length);

    unsigned left_over = length % 3;

    if (left_over) {
        in -= left_over;
        *--out = '=';
        switch(left_over) {
        case 1:
            *--out = '=';
            *--out = ENCODE(in[0] << 4);
            break;

        case 2:
            *--out = ENCODE( in[1] << 2);
            *--out = ENCODE((in[0] << 4) | (in[1] >> 4));
            break;

        default:
            abort();
        }
        *--out = ENCODE(in[0] >> 2);
    }

    while (in > src) {
        in -= 3;
        *--out = ENCODE( in[2]);
        *--out = ENCODE((in[1] << 2) | (in[2] >> 6));
        *--out = ENCODE((in[0] << 4) | (in[1] >> 4));
        *--out = ENCODE( in[0] >> 2);
    }
    assert(in == src);
    assert(out == dst);
}