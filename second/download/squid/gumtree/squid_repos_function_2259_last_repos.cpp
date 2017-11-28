int
HttpHeader::delById(Http::HdrType id)
{
    debugs(55, 8, this << " del-by-id " << id);
    assert(any_registered_header(id));

    if (!CBIT_TEST(mask, id))
        return 0;

    int count = 0;

    HttpHeaderPos pos = HttpHeaderInitPos;
    while (HttpHeaderEntry *e = getEntry(&pos)) {
        if (e->id == id)
            delAt(pos, count); // deletes e
    }

    CBIT_CLR(mask, id);
    assert(count);
    return count;
}