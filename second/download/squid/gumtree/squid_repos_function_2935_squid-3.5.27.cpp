void ChunkedCodingParser::parseChunkBody()
{
    Must(theLeftBodySize > 0); // Should, really

    const size_t availSize = min(theLeftBodySize, (uint64_t)theIn->contentSize());
    const size_t safeSize = min(availSize, (size_t)theOut->potentialSpaceSize());

    doNeedMoreData = availSize < theLeftBodySize;
    // and we may also need more space

    theOut->append(theIn->content(), safeSize);
    theIn->consume(safeSize);
    theLeftBodySize -= safeSize;

    if (theLeftBodySize == 0)
        theStep = psChunkEnd;
    else
        Must(needsMoreData() || needsMoreSpace());
}