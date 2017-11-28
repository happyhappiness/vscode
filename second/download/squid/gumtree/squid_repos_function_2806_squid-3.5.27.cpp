void
HttpHeader::insertEntry(HttpHeaderEntry * e)
{
    assert(e);
    assert_eid(e->id);

    debugs(55, 7, this << " adding entry: " << e->id << " at " << entries.size());

    if (CBIT_TEST(mask, e->id))
        ++ Headers[e->id].stat.repCount;
    else
        CBIT_SET(mask, e->id);

    entries.insert(entries.begin(),e);

    /* increment header length, allow for ": " and crlf */
    len += e->name.size() + 2 + e->value.size() + 2;
}