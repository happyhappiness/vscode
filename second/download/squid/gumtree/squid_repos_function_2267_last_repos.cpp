String
HttpHeader::getStrOrList(Http::HdrType id) const
{
    HttpHeaderEntry *e;

    if (Http::HeaderLookupTable.lookup(id).list)
        return getList(id);

    if ((e = findEntry(id)))
        return e->value;

    return String();
}