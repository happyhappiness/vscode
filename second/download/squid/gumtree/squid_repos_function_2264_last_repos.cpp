void
HttpHeader::insertEntry(HttpHeaderEntry * e)
{
    assert(e);
    assert(any_valid_header(e->id));

    debugs(55, 7, this << " adding entry: " << e->id << " at " << entries.size());

    // Http::HdrType::BAD_HDR is filtered out by assert_any_valid_header
    if (CBIT_TEST(mask, e->id)) {
        ++ headerStatsTable[e->id].repCount;
    } else {
        CBIT_SET(mask, e->id);
    }

    entries.insert(entries.begin(),e);

    /* increment header length, allow for ": " and crlf */
    len += e->name.size() + 2 + e->value.size() + 2;
}