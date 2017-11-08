int deflateInit2 (strm, level, method, windowBits, memLevel, strategy)
    z_stream *strm;
    int  level;
    int  method;
    int  windowBits;
    int  memLevel;
    int  strategy;
{
    deflate_state *s;
    int noheader = 0;

    if (strm == Z_NULL) return Z_STREAM_ERROR;

    strm->msg = Z_NULL;
/*    if (strm->zalloc == Z_NULL) strm->zalloc = zcalloc; */
/*    if (strm->zfree == Z_NULL) strm->zfree = zcfree; */

    if (level == Z_DEFAULT_COMPRESSION) level = 6;

    if (windowBits < 0) { /* undocumented feature: suppress zlib header */
        noheader = 1;
        windowBits = -windowBits;
    }
    if (memLevel < 1 || memLevel > MAX_MEM_LEVEL || method != DEFLATED ||
        windowBits < 8 || windowBits > 15 || level < 1 || level > 9) {
        return Z_STREAM_ERROR;
    }
    s = (deflate_state *) ZALLOC(strm, 1, sizeof(deflate_state));
    if (s == Z_NULL) return Z_MEM_ERROR;
    bzero(s, sizeof(*s));
    strm->state = (struct internal_state FAR *)s;
    s->strm = strm;

    s->noheader = noheader;
    s->w_bits = windowBits;
    s->w_size = 1 << s->w_bits;
    s->w_mask = s->w_size - 1;

    s->hash_bits = memLevel + 7;
    s->hash_size = 1 << s->hash_bits;
    s->hash_mask = s->hash_size - 1;
    s->hash_shift =  ((s->hash_bits+MIN_MATCH-1)/MIN_MATCH);

    s->window = (Bytef *) ZALLOC(strm, s->w_size, 2*sizeof(Byte));
    s->prev   = (Posf *)  ZALLOC(strm, s->w_size, sizeof(Pos));
    s->head   = (Posf *)  ZALLOC(strm, s->hash_size, sizeof(Pos));

    s->lit_bufsize = 1 << (memLevel + 6); /* 16K elements by default */

    s->pending_buf = (uchf *) ZALLOC(strm, s->lit_bufsize, 2*sizeof(ush));

    if (s->window == Z_NULL || s->prev == Z_NULL || s->head == Z_NULL ||
        s->pending_buf == Z_NULL) {
        strm->msg = z_errmsg[1-Z_MEM_ERROR];
        deflateEnd (strm);
        return Z_MEM_ERROR;
    }
    s->d_buf = (ushf *) &(s->pending_buf[s->lit_bufsize]);
    s->l_buf = (uchf *) &(s->pending_buf[3*s->lit_bufsize]);
    /* We overlay pending_buf and d_buf+l_buf. This works since the average
     * output size for (length,distance) codes is <= 32 bits (worst case
     * is 15+15+13=33).
     */

    s->level = level;
    s->strategy = strategy;
    s->method = (Byte)method;
    s->blocks_in_packet = 0;

    return deflateReset(strm);
}