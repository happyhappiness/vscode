void ChunkedCodingParser::parseLastChunkExtension()
{
    size_t crlfBeg = 0;
    size_t crlfEnd = 0;

    if (!findCrlf(crlfBeg, crlfEnd)) {
        doNeedMoreData = true;
        return;
    }

    const char *const startExt = theIn->content();
    const char *const endExt = theIn->content() + crlfBeg;

    // chunk-extension starts at startExt and ends with LF at endEx
    for (const char *p = startExt; p < endExt;) {

        while (*p == ' ' || *p == '\t') ++p; // skip spaces before ';'

        if (*p++ != ';') // each ext name=value pair is preceded with ';'
            break;

        while (*p == ' ' || *p == '\t') ++p; // skip spaces before name

        if (p >= endExt)
            break; // malformed extension: ';' without ext name=value pair

        const int extSize = endExt - p;
        // TODO: we need debugData() stream manipulator to dump data
        debugs(94,7, "Found chunk extension; size=" << extSize);

        // TODO: support implied *LWS around '='
        if (extSize > 18 && strncmp(p, "use-original-body=", 18) == 0) {
            (void)StringToInt64(p+18, useOriginBody, &p, 10);
            debugs(94, 3, HERE << "use-original-body=" << useOriginBody);
            break; // remove to support more than just use-original-body
        } else {
            debugs(94, 5, HERE << "skipping unknown chunk extension");
            // TODO: support quoted-string chunk-ext-val
            while (p < endExt && *p != ';') ++p; // skip until the next ';'
        }
    }

    theIn->consume(crlfEnd);
    theStep = theChunkSize ? psChunkBody : psTrailer;
}