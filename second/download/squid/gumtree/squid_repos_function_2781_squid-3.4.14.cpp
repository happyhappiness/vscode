void
HttpHeader::append(const HttpHeader * src)
{
    const HttpHeaderEntry *e;
    HttpHeaderPos pos = HttpHeaderInitPos;
    assert(src);
    assert(src != this);
    debugs(55, 7, "appending hdr: " << this << " += " << src);

    while ((e = src->getEntry(&pos))) {
        addEntry(e->clone());
    }
}