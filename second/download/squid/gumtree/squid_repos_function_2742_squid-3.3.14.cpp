int
HttpHeader::delById(http_hdr_type id)
{
    int count = 0;
    HttpHeaderPos pos = HttpHeaderInitPos;
    HttpHeaderEntry *e;
    debugs(55, 8, this << " del-by-id " << id);
    assert_eid(id);
    assert(id != HDR_OTHER);		/* does not make sense */

    if (!CBIT_TEST(mask, id))
        return 0;

    while ((e = getEntry(&pos))) {
        if (e->id == id)
            delAt(pos, count);
    }

    CBIT_CLR(mask, id);
    assert(count);
    return count;
}