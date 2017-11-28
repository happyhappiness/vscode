void
HttpHeader::addEntry(HttpHeaderEntry * e)
{
    assert(e);
    assert(any_HdrType_enum_value(e->id));
    assert(e->name.size());

    debugs(55, 7, this << " adding entry: " << e->id << " at " << entries.size());

    if (e->id != Http::HdrType::BAD_HDR) {
        if (CBIT_TEST(mask, e->id)) {
            ++ headerStatsTable[e->id].repCount;
        } else {
            CBIT_SET(mask, e->id);
        }
    }

    entries.push_back(e);

    /* increment header length, allow for ": " and crlf */
    len += e->name.size() + 2 + e->value.size() + 2;
}