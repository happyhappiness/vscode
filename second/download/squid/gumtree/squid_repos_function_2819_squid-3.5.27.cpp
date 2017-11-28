void
HttpHeader::putStr(http_hdr_type id, const char *str)
{
    assert_eid(id);
    assert(Headers[id].type == ftStr);  /* must be of an appropriate type */
    assert(str);
    addEntry(new HttpHeaderEntry(id, NULL, str));
}