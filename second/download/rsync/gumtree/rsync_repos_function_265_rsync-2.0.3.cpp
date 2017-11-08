local void ct_stored_type_only(s)
    deflate_state *s;
{
    send_bits(s, (STORED_BLOCK << 1), 3);
    bi_windup(s);
    s->compressed_len = (s->compressed_len + 3) & ~7L;
}