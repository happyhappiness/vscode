void
HttpHeader::delAt(HttpHeaderPos pos, int &headers_deleted)
{
    HttpHeaderEntry *e;
    assert(pos >= HttpHeaderInitPos && pos < (ssize_t)entries.count);
    e = (HttpHeaderEntry*)entries.items[pos];
    entries.items[pos] = NULL;
    /* decrement header length, allow for ": " and crlf */
    len -= e->name.size() + 2 + e->value.size() + 2;
    assert(len >= 0);
    delete e;
    ++headers_deleted;
}