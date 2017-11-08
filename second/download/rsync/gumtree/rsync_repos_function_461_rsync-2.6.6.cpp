int ZEXPORT deflatePrime (strm, bits, value)
    z_streamp strm;
    int bits;
    int value;
{
    if (strm == Z_NULL || strm->state == Z_NULL) return Z_STREAM_ERROR;
    strm->state->bi_valid = bits;
    strm->state->bi_buf = (ush)(value & ((1 << bits) - 1));
    return Z_OK;
}