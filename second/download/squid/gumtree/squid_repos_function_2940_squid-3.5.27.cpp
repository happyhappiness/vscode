bool ChunkedCodingParser::findCrlf(size_t &crlfBeg, size_t &crlfEnd)
{
    bool quoted = false;
    bool slashed = false;
    return findCrlf(crlfBeg, crlfEnd, quoted, slashed);
}