bool
HttpRequest::parseFirstLine(const char *start, const char *end)
{
    const char *t = start + strcspn(start, w_space);
    method = HttpRequestMethod(start, t);

    if (method == METHOD_NONE)
        return false;

    start = t + strspn(t, w_space);

    const char *ver = findTrailingHTTPVersion(start, end);

    if (ver) {
        end = ver - 1;

        while (xisspace(*end)) // find prev non-space
            end--;

        end++;                 // back to space

        if (2 != sscanf(ver + 5, "%d.%d", &http_ver.major, &http_ver.minor)) {
            debugs(73, 1, "parseRequestLine: Invalid HTTP identifier.");
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

    HttpRequest *tmp = urlParse(method, (char *) start, this);

    * (char *) end = save;

    if (NULL == tmp)
        return false;

    return true;
}