void ChunkedCodingParser::parseTrailer()
{
    Must(theChunkSize == 0); // Should(), really

    while (mayContinue())
        parseTrailerHeader();
}