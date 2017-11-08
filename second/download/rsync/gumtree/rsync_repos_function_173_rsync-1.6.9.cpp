local void copy_block(s, buf, len, header)
    deflate_state *s;
    charf    *buf;    /* the input data */
    unsigned len;     /* its length */
    int      header;  /* true if block header must be written */
{
    bi_windup(s);        /* align on byte boundary */
    s->last_eob_len = 8; /* enough lookahead for inflate */

    if (header) {
        put_short(s, (ush)len);   
        put_short(s, (ush)~len);
#ifdef DEBUG_ZLIB
        s->bits_sent += 2*16;
#endif
    }
#ifdef DEBUG_ZLIB
    s->bits_sent += (ulg)len<<3;
#endif
    while (len--) {
        put_byte(s, *buf++);
    }
}