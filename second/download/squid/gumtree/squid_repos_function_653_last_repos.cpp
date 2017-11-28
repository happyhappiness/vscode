static int
httpMsgIsolateStart(const char **parse_start, const char **blk_start, const char **blk_end)
{
    int slen = strcspn(*parse_start, "\r\n");

    if (!(*parse_start)[slen])  /* no CRLF found */
        return 0;

    *blk_start = *parse_start;

    *blk_end = *blk_start + slen;

    while (**blk_end == '\r')   /* CR */
        ++(*blk_end);

    if (**blk_end == '\n')      /* LF */
        ++(*blk_end);

    *parse_start = *blk_end;

    return 1;
}