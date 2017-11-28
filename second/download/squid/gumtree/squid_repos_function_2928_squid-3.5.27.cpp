void ChunkedCodingParser::reset()
{
    theStep = psChunkSize;
    theChunkSize = theLeftBodySize = 0;
    doNeedMoreData = false;
    theIn = theOut = NULL;
    useOriginBody = -1;
    inQuoted = inSlashed = false;
}