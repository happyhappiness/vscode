void
HttpHeader::putTime(Http::HdrType id, time_t htime)
{
    assert(any_registered_header(id));
    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftDate_1123);    /* must be of an appropriate type */
    assert(htime >= 0);
    addEntry(new HttpHeaderEntry(id, NULL, mkrfc1123(htime)));
}