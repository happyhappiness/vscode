bool ChunkedCodingParser::mayContinue() const
{
    return !needsMoreData() && !needsMoreSpace() && theStep != psMessageEnd;
}