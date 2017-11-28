void
HttpRequestMethod::HttpRequestMethodXXX(char const *begin)
{
    // XXX: performance regression due to this method no longer being a constructor
    // ensure the members are empty/default values before any of the early-return
    // optimizations can be used.
    theMethod = Http::METHOD_NONE;
    theImage.clear();

    if (begin == NULL)
        return;

    char const *end = begin + strcspn(begin, w_space);

    if (end == begin)
        return;

    // TODO: Optimize this linear search.
    for (++theMethod; theMethod < Http::METHOD_ENUM_END; ++theMethod) {
        // RFC 2616 section 5.1.1 - Method names are case-sensitive
        // NP: this is not a HTTP_VIOLATIONS case since there is no MUST/SHOULD involved.
        if (0 == image().caseCmp(begin, end-begin)) {

            // relaxed parser allows mixed-case and corrects them on output
            if (Config.onoff.relaxed_header_parser)
                return;

            if (0 == image().cmp(begin, end-begin))
                return;
        }
    }

    // if method not found and method string is not null then it is other method
    theMethod = Http::METHOD_OTHER;
    theImage.assign(begin, end-begin);
}