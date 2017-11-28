HttpHeaderEntry *
HttpHeader::findEntry(http_hdr_type id) const
{
    HttpHeaderPos pos = HttpHeaderInitPos;
    HttpHeaderEntry *e;
    assert_eid(id);
    assert(!CBIT_TEST(ListHeadersMask, id));

    /* check mask first */

    if (!CBIT_TEST(mask, id))
        return NULL;

    /* looks like we must have it, do linear search */
    while ((e = getEntry(&pos))) {
        if (e->id == id)
            return e;
    }

    /* hm.. we thought it was there, but it was not found */
    assert(0);

    return NULL;        /* not reached */
}