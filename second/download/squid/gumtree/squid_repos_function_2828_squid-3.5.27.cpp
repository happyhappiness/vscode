int64_t
HttpHeader::getInt64(http_hdr_type id) const
{
    assert_eid(id);
    assert(Headers[id].type == ftInt64);    /* must be of an appropriate type */
    HttpHeaderEntry *e;

    if ((e = findEntry(id)))
        return e->getInt64();

    return -1;
}