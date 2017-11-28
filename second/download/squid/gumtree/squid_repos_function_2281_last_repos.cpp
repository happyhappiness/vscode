void
HttpHeader::putStr(Http::HdrType id, const char *str)
{
    assert(any_registered_header(id));
    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftStr);  /* must be of an appropriate type */
    assert(str);
    addEntry(new HttpHeaderEntry(id, NULL, str));
}