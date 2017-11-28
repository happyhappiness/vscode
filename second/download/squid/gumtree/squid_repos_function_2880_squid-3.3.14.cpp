void ChunkedCodingParser::parseTrailerHeader()
{
    size_t crlfBeg = 0;
    size_t crlfEnd = 0;

    if (findCrlf(crlfBeg, crlfEnd)) {

#if TRAILERS_ARE_SUPPORTED
        if (crlfBeg > 0)
            theTrailer.append(theIn->content(), crlfEnd);
#endif

        theIn->consume(crlfEnd);

        if (crlfBeg == 0)
            theStep = psMessageEnd;

        return;
    }

    doNeedMoreData = true;
}