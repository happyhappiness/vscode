static void
gopher_request_parse(const HttpRequest * req, char *type_id, char *request)
{
    const char *path = req->urlpath.termedBuf();

    if (request)
        request[0] = '\0';

    if (path && (*path == '/'))
        path++;

    if (!path || !*path) {
        *type_id = GOPHER_DIRECTORY;
        return;
    }

    *type_id = path[0];

    if (request) {
        xstrncpy(request, path + 1, MAX_URL);
        /* convert %xx to char */
        rfc1738_unescape(request);
    }
}