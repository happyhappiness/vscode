void
HttpHeader::delAt(HttpHeaderPos pos, int &headers_deleted)
{
    HttpHeaderEntry *e;
    assert(pos >= HttpHeaderInitPos && pos < static_cast<ssize_t>(entries.size()));
    e = static_cast<HttpHeaderEntry*>(entries[pos]);
    entries[pos] = NULL;
    /* decrement header length, allow for ": " and crlf */
    len -= e->name.size() + 2 + e->value.size() + 2;
    assert(len >= 0);
    delete e;
    ++headers_deleted;
}