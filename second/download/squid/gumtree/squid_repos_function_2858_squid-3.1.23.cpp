bool ChunkedCodingParser::findCrlf(size_t &crlfBeg, size_t &crlfEnd)
{
    // XXX: This code was copied, with permission, from another software.
    // There is a similar and probably better code inside httpHeaderParse
    // but it seems difficult to isolate due to parsing-unrelated bloat.
    // Such isolation should probably be done before this class is used
    // for handling of traffic "more external" than ICAP.

    const char *buf = theIn->content();
    size_t size = theIn->contentSize();

    ssize_t crOff = -1;
    bool quoted = false;
    bool slashed = false;

    for (size_t i = 0; i < size; ++i) {
        if (slashed) {
            slashed = false;
            continue;
        }

        const char c = buf[i];

        // handle quoted strings
        if (quoted) {
            if (c == '\\')
                slashed = true;
            else if (c == '"')
                quoted = false;

            continue;
        } else if (c == '"') {
            quoted = true;
            crOff = -1;
            continue;
        }

        if (crOff < 0) { // looking for the first CR or LF

            if (c == '\n') {
                crlfBeg = i;
                crlfEnd = ++i;
                return true;
            }

            if (c == '\r')
                crOff = i;
        } else { // skipping CRs, looking for the first LF

            if (c == '\n') {
                crlfBeg = crOff;
                crlfEnd = ++i;
                return true;
            }

            if (c != '\r')
                crOff = -1;
        }
    }

    return false;
}