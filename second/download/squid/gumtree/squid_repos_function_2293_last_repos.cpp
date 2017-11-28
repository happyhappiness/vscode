const char *
HttpHeader::getLastStr(Http::HdrType id) const
{
    HttpHeaderEntry *e;
    assert(any_registered_header(id));
    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftStr);  /* must be of an appropriate type */

    if ((e = findLastEntry(id))) {
        httpHeaderNoteParsedEntry(e->id, e->value, false);  /* no errors are possible */
        return e->value.termedBuf();
    }

    return NULL;
}