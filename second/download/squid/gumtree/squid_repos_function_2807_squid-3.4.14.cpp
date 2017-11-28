void
HttpHeader::putTime(http_hdr_type id, time_t htime)
{
    assert_eid(id);
    assert(Headers[id].type == ftDate_1123);	/* must be of an appropriate type */
    assert(htime >= 0);
    addEntry(new HttpHeaderEntry(id, NULL, mkrfc1123(htime)));
}