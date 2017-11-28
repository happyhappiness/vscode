bool
HttpRequest::parseFirstLine(const char *start, const char *end)
{
    method.HttpRequestMethodXXX(start);

    if (method == Http::METHOD_NONE)
        return false;

    // XXX: performance regression, strcspn() over the method bytes a second time.
    // cheaper than allocate+copy+deallocate cycle to SBuf convert a piece of start.
    const char *t = start + strcspn(start, w_space);

    start = t + strspn(t, w_space); // skip w_space after method

    const char *ver = findTrailingHTTPVersion(start, end);

    if (ver) {
        end = ver - 1;

        while (xisspace(*end)) // find prev non-space
            --end;

        ++end;                 // back to space

        if (2 != sscanf(ver + 5, "%d.%d", &http_ver.major, &http_ver.minor)) {
            debugs(73, DBG_IMPORTANT, "parseRequestLine: Invalid HTTP identifier.");
            return false;
        }
    } else {
        http_ver.major = 0;
        http_ver.minor = 9;
    }

    if (end < start)   // missing URI
        return false;

    char save = *end;

    * (char *) end = '\0';     // temp terminate URI, XXX dangerous?

    const bool ret = url.parse(method, (char *) start);

    * (char *) end = save;

    return ret;
}