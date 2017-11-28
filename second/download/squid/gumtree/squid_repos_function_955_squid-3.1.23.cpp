int
httpMsgIsolateHeaders(const char **parse_start, int l, const char **blk_start, const char **blk_end)
{
    /*
     * parse_start points to the first line of HTTP message *headers*,
     * not including the request or status lines
     */
    size_t end = headersEnd(*parse_start, l);
    int nnl;

    if (end) {
        *blk_start = *parse_start;
        *blk_end = *parse_start + end - 1;
        /*
         * leave blk_end pointing to the first character after the
         * first newline which terminates the headers
         */
        assert(**blk_end == '\n');

        while (*(*blk_end - 1) == '\r')
            (*blk_end)--;

        assert(*(*blk_end - 1) == '\n');

        *parse_start += end;

        return 1;
    }

    /*
     * If we didn't find the end of headers, and parse_start does
     * NOT point to a CR or NL character, then return failure
     */
    if (**parse_start != '\r' && **parse_start != '\n')
        return 0;		/* failure */

    /*
     * If we didn't find the end of headers, and parse_start does point
     * to an empty line, then we have empty headers.  Skip all CR and
     * NL characters up to the first NL.  Leave parse_start pointing at
     * the first character after the first NL.
     */
    *blk_start = *parse_start;

    *blk_end = *blk_start;

    for (nnl = 0; nnl == 0; (*parse_start)++) {
        if (**parse_start == '\r')
            (void) 0;
        else if (**parse_start == '\n')
            nnl++;
        else
            break;
    }

    return 1;
}