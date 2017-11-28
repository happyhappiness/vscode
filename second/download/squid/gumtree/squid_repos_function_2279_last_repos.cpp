void
HttpHeader::putInt64(Http::HdrType id, int64_t number)
{
    assert(any_registered_header(id));
    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftInt64);    /* must be of an appropriate type */
    assert(number >= 0);
    addEntry(new HttpHeaderEntry(id, NULL, xint64toa(number)));
}