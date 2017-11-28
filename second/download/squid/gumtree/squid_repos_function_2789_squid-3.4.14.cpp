HttpHeaderEntry *
HttpHeader::findLastEntry(http_hdr_type id) const
{
    HttpHeaderPos pos = HttpHeaderInitPos;
    HttpHeaderEntry *e;
    HttpHeaderEntry *result = NULL;
    assert_eid(id);
    assert(!CBIT_TEST(ListHeadersMask, id));

    /* check mask first */

    if (!CBIT_TEST(mask, id))
        return NULL;

    /* looks like we must have it, do linear search */
    while ((e = getEntry(&pos))) {
        if (e->id == id)
            result = e;
    }

    assert(result);		/* must be there! */
    return result;
}