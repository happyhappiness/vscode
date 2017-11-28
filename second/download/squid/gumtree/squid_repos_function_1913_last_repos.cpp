void
httpHdrMangleList(HttpHeader *l, HttpRequest *request, const AccessLogEntryPointer &al, req_or_rep_t req_or_rep)
{
    HttpHeaderEntry *e;
    HttpHeaderPos p = HttpHeaderInitPos;

    /* check with anonymizer tables */
    HeaderManglers *hms = nullptr;
    HeaderWithAclList *headersAdd = nullptr;

    switch (req_or_rep) {
    case ROR_REQUEST:
        hms = Config.request_header_access;
        headersAdd = Config.request_header_add;
        break;
    case ROR_REPLY:
        hms = Config.reply_header_access;
        headersAdd = Config.reply_header_add;
        break;
    }

    if (hms) {
        int headers_deleted = 0;
        while ((e = l->getEntry(&p))) {
            if (0 == httpHdrMangle(e, request, hms))
                l->delAt(p, headers_deleted);
        }

        if (headers_deleted)
            l->refreshMask();
    }

    if (headersAdd && !headersAdd->empty()) {
        httpHdrAdd(l, request, al, *headersAdd);
    }
}