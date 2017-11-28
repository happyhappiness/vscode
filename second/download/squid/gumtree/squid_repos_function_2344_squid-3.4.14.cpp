void
httpHdrMangleList(HttpHeader * l, HttpRequest * request, int req_or_rep)
{
    HttpHeaderEntry *e;
    HttpHeaderPos p = HttpHeaderInitPos;

    int headers_deleted = 0;
    while ((e = l->getEntry(&p)))
        if (0 == httpHdrMangle(e, request, req_or_rep))
            l->delAt(p, headers_deleted);

    if (headers_deleted)
        l->refreshMask();
}