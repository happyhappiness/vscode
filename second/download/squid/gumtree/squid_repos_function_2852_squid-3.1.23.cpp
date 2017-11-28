void ChunkedCodingParser::parseChunkBeg()
{
    Must(theChunkSize <= 0); // Should(), really

    size_t crlfBeg = 0;
    size_t crlfEnd = 0;

    if (findCrlf(crlfBeg, crlfEnd)) {
        debugs(94,7, "found chunk-size end: " << crlfBeg << "-" << crlfEnd);
        int64_t size = -1;
        const char *p = 0;

        if (StringToInt64(theIn->content(), size, &p, 16)) {
            if (size < 0) {
                throw TexcHere("negative chunk size");
                return;
            }

            theIn->consume(crlfEnd);
            theChunkSize = theLeftBodySize = size;
            debugs(94,7, "found chunk: " << theChunkSize);
            theStep = theChunkSize == 0 ? psTrailer : psChunkBody;
            return;
        }

        throw TexcHere("corrupted chunk size");
    }

    doNeedMoreData = true;
}