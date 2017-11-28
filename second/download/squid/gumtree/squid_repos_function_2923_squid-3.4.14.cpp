void ChunkedCodingParser::parseChunkSize()
{
    Must(theChunkSize <= 0); // Should(), really

    const char *p = theIn->content();
    while (p < theIn->space() && xisxdigit(*p)) ++p;
    if (p >= theIn->space()) {
        doNeedMoreData = true;
        return;
    }

    int64_t size = -1;
    if (StringToInt64(theIn->content(), size, &p, 16)) {
        if (size < 0)
            throw TexcHere("negative chunk size");

        theChunkSize = theLeftBodySize = size;
        debugs(94,7, "found chunk: " << theChunkSize);
        // parse chunk extensions only in the last-chunk
        if (theChunkSize)
            theStep = psUnusedChunkExtension;
        else {
            theIn->consume(p - theIn->content());
            theStep = psLastChunkExtension;
        }
    } else
        throw TexcHere("corrupted chunk size");
}