bool ChunkedCodingParser::parse(MemBuf *rawData, MemBuf *parsedContent)
{
    Must(rawData && parsedContent);
    theIn = rawData;
    theOut = parsedContent;

    // we must reset this all the time so that mayContinue() lets us
    // output more content if we stopped due to needsMoreSpace() before
    doNeedMoreData = !theIn->hasContent();

    while (mayContinue()) {
        (this->*theStep)();
    }

    return theStep == psMessageEnd;
}