void
HttpRequest::pack(Packer * p)
{
    assert(p);
    /* pack request-line */
    packerPrintf(p, "%s " SQUIDSTRINGPH " HTTP/%d.%d\r\n",
                 RequestMethodStr(method), SQUIDSTRINGPRINT(urlpath),
                 http_ver.major, http_ver.minor);
    /* headers */
    header.packInto(p);
    /* trailer */
    packerAppend(p, "\r\n", 2);
}