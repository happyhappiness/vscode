void
HttpHeader::addEntry(HttpHeaderEntry * e)
{
    assert(e);
    assert_eid(e->id);
    assert(e->name.size());

    debugs(55, 7, this << " adding entry: " << e->id << " at " << entries.size());

    if (CBIT_TEST(mask, e->id))
        ++ Headers[e->id].stat.repCount;
    else
        CBIT_SET(mask, e->id);

    entries.push_back(e);

    /* increment header length, allow for ": " and crlf */
    len += e->name.size() + 2 + e->value.size() + 2;
}