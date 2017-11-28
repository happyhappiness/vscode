void ChunkedCodingParser::parseChunkEnd()
{
    Must(theLeftBodySize == 0); // Should(), really

    size_t crlfBeg = 0;
    size_t crlfEnd = 0;

    if (findCrlf(crlfBeg, crlfEnd)) {
        if (crlfBeg != 0) {
            throw TexcHere("found data between chunk end and CRLF");
            return;
        }

        theIn->consume(crlfEnd);
        theChunkSize = 0; // done with the current chunk
        theStep = psChunkBeg;
        return;
    }

    doNeedMoreData = true;
}