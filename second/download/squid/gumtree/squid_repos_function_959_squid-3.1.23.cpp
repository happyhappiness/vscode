int
HttpMsg::httpMsgParseStep(const char *buf, int len, int atEnd)
{
    const char *parse_start = buf;
    int parse_len = len;
    const char *blk_start, *blk_end;
    const char **parse_end_ptr = &blk_end;
    assert(parse_start);
    assert(pstate < psParsed);

    *parse_end_ptr = parse_start;

    PROF_start(HttpMsg_httpMsgParseStep);

    if (pstate == psReadyToParseStartLine) {
        if (!httpMsgIsolateStart(&parse_start, &blk_start, &blk_end)) {
            PROF_stop(HttpMsg_httpMsgParseStep);
            return 0;
        }

        if (!parseFirstLine(blk_start, blk_end)) {
            PROF_stop(HttpMsg_httpMsgParseStep);
            return httpMsgParseError();
        }

        *parse_end_ptr = parse_start;

        hdr_sz = *parse_end_ptr - buf;
        parse_len = parse_len - hdr_sz;

        ++pstate;
    }

    /*
     * XXX This code uses parse_start; but if we're incrementally parsing then
     * this code might not actually be given parse_start at the right spot (just
     * after headers.) Grr.
     */
    if (pstate == psReadyToParseHeaders) {
        if (!httpMsgIsolateHeaders(&parse_start, parse_len, &blk_start, &blk_end)) {
            if (atEnd) {
                blk_start = parse_start, blk_end = blk_start + strlen(blk_start);
            } else {
                PROF_stop(HttpMsg_httpMsgParseStep);
                return 0;
            }
        }

        if (!header.parse(blk_start, blk_end)) {
            PROF_stop(HttpMsg_httpMsgParseStep);
            return httpMsgParseError();
        }

        hdrCacheInit();

        *parse_end_ptr = parse_start;

        hdr_sz = *parse_end_ptr - buf;

        ++pstate;
    }

    PROF_stop(HttpMsg_httpMsgParseStep);
    return 1;
}