void ChunkedCodingParser::reset()
{
    theStep = psChunkBeg;
    theChunkSize = theLeftBodySize = 0;
    doNeedMoreData = false;
    theIn = theOut = NULL;
}