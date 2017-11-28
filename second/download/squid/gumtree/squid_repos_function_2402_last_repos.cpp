void
HttpRequest::pack(Packable * p) const
{
    assert(p);
    /* pack request-line */
    p->appendf(SQUIDSBUFPH " " SQUIDSBUFPH " HTTP/%d.%d\r\n",
               SQUIDSBUFPRINT(method.image()), SQUIDSBUFPRINT(url.path()),
               http_ver.major, http_ver.minor);
    /* headers */
    header.packInto(p);
    /* trailer */
    p->append("\r\n", 2);
}