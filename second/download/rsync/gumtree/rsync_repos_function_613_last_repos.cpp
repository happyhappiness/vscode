void ZLIB_INTERNAL _tr_flush_bits(s)
    deflate_state *s;
{
    bi_flush(s);
}