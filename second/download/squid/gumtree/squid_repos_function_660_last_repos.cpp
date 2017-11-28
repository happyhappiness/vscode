bool
HttpMsg::persistent() const
{
    if (http_ver > Http::ProtocolVersion(1,0)) {
        /*
         * for modern versions of HTTP: persistent unless there is
         * a "Connection: close" header.
         */
        return !httpHeaderHasConnDir(&header, "close");
    } else {
        /* for old versions of HTTP: persistent if has "keep-alive" */
        return httpHeaderHasConnDir(&header, "keep-alive");
    }
}