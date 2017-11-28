void
HttpRequest::pack(Packer * p)
{
    assert(p);
    /* pack request-line */
    packerPrintf(p, SQUIDSBUFPH " " SQUIDSTRINGPH " HTTP/%d.%d\r\n",
                 SQUIDSBUFPRINT(method.image()), SQUIDSTRINGPRINT(urlpath),
                 http_ver.major, http_ver.minor);
    /* headers */
    header.packInto(p);
    /* trailer */
    packerAppend(p, "\r\n", 2);
}