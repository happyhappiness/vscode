void
HttpHeader::putInt64(http_hdr_type id, int64_t number)
{
    assert_eid(id);
    assert(Headers[id].type == ftInt64);    /* must be of an appropriate type */
    assert(number >= 0);
    addEntry(new HttpHeaderEntry(id, NULL, xint64toa(number)));
}