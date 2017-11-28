void HttpRequest::packFirstLineInto(Packer * p, bool full_uri) const
{
    // form HTTP request-line
    packerPrintf(p, "%s %s HTTP/%d.%d\r\n",
                 RequestMethodStr(method),
                 packableURI(full_uri),
                 http_ver.major, http_ver.minor);
}