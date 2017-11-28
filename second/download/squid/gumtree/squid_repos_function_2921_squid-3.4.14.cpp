bool ChunkedCodingParser::needsMoreSpace() const
{
    assert(theOut);
    return theStep == psChunkBody && !theOut->hasPotentialSpace();
}