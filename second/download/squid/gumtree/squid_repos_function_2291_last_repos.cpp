time_t
HttpHeader::getTime(Http::HdrType id) const
{
    HttpHeaderEntry *e;
    time_t value = -1;
    assert(any_registered_header(id));
    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftDate_1123);    /* must be of an appropriate type */

    if ((e = findEntry(id))) {
        value = parse_rfc1123(e->value.termedBuf());
        httpHeaderNoteParsedEntry(e->id, e->value, value < 0);
    }

    return value;
}