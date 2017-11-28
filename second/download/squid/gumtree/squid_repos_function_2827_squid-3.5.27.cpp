int
HttpHeader::getInt(http_hdr_type id) const
{
    assert_eid(id);
    assert(Headers[id].type == ftInt);  /* must be of an appropriate type */
    HttpHeaderEntry *e;

    if ((e = findEntry(id)))
        return e->getInt();

    return -1;
}