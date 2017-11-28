int
httpMsgIsPersistent(HttpVersion const &http_ver, const HttpHeader * hdr)
{
    if (http_ver > HttpVersion(1, 0)) {
        /*
         * for modern versions of HTTP: persistent unless there is
         * a "Connection: close" header.
         */
        return !httpHeaderHasConnDir(hdr, "close");
    } else {
        /* for old versions of HTTP: persistent if has "keep-alive" */
        return httpHeaderHasConnDir(hdr, "keep-alive");
    }
}