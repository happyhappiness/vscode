void ChunkedCodingParser::parseUnusedChunkExtension()
{
    size_t crlfBeg = 0;
    size_t crlfEnd = 0;
    if (findCrlf(crlfBeg, crlfEnd, inQuoted, inSlashed)) {
        inQuoted = inSlashed = false;
        theIn->consume(crlfEnd);
        theStep = theChunkSize ? psChunkBody : psTrailer;
    } else {
        theIn->consume(theIn->contentSize());
        doNeedMoreData = true;
    }
}