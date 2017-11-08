int deflateInit (strm, level)
    z_stream *strm;
    int level;
{
    return deflateInit2 (strm, level, DEFLATED, MAX_WBITS, DEF_MEM_LEVEL, 0);
    /* To do: ignore strm->next_in if we use it as window */
}