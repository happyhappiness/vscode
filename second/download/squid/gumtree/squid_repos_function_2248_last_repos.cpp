void
HttpHeader::append(const HttpHeader * src)
{
    assert(src);
    assert(src != this);
    debugs(55, 7, "appending hdr: " << this << " += " << src);

    for (auto e : src->entries) {
        if (e)
            addEntry(e->clone());
    }
}