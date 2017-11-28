int
HttpHeader::getInt(Http::HdrType id) const
{
    assert(any_registered_header(id));
    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftInt);  /* must be of an appropriate type */
    HttpHeaderEntry *e;

    if ((e = findEntry(id)))
        return e->getInt();

    return -1;
}