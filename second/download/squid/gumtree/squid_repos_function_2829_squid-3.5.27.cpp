time_t
HttpHeader::getTime(http_hdr_type id) const
{
    HttpHeaderEntry *e;
    time_t value = -1;
    assert_eid(id);
    assert(Headers[id].type == ftDate_1123);    /* must be of an appropriate type */

    if ((e = findEntry(id))) {
        value = parse_rfc1123(e->value.termedBuf());
        httpHeaderNoteParsedEntry(e->id, e->value, value < 0);
    }

    return value;
}