HttpHeaderEntry *
HttpHeader::findLastEntry(Http::HdrType id) const
{
    assert(any_registered_header(id));
    assert(!Http::HeaderLookupTable.lookup(id).list);

    /* check mask first */
    if (!CBIT_TEST(mask, id))
        return NULL;

    for (auto e = entries.rbegin(); e != entries.rend(); ++e) {
        if (*e && (*e)->id == id)
            return *e;
    }

    /* hm.. we thought it was there, but it was not found */
    assert(false);
    return nullptr; /* not reached */
}