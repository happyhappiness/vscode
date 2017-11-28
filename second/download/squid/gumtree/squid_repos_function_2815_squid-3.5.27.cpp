void
HttpHeader::putInt(http_hdr_type id, int number)
{
    assert_eid(id);
    assert(Headers[id].type == ftInt);  /* must be of an appropriate type */
    assert(number >= 0);
    addEntry(new HttpHeaderEntry(id, NULL, xitoa(number)));
}