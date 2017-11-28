int
HttpRequest::parseHeader(const char *parse_start, int len)
{
    const char *blk_start, *blk_end;

    if (!httpMsgIsolateHeaders(&parse_start, len, &blk_start, &blk_end))
        return 0;

    int result = header.parse(blk_start, blk_end);

    if (result)
        hdrCacheInit();

    return result;
}