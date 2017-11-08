local int zread_buf(strm, buf, size)
    z_stream *strm;
    charf *buf;
    unsigned size;
{
    unsigned len = strm->avail_in;
    deflate_state *state = (deflate_state *) strm->state;

    if (len > size) len = size;
    if (len == 0) return 0;

    strm->avail_in  -= len;

    if (!state->noheader) {
        state->adler = adler32(state->adler, strm->next_in, len);
    }
    zmemcpy(buf, strm->next_in, len);
    strm->next_in  += len;
    strm->total_in += len;

    return (int)len;
}