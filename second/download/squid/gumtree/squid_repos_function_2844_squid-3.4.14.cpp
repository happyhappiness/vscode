void
HttpHeader::removeHopByHopEntries()
{
    removeConnectionHeaderEntries();

    const HttpHeaderEntry *e;
    HttpHeaderPos pos = HttpHeaderInitPos;
    int headers_deleted = 0;
    while ((e = getEntry(&pos))) {
        int id = e->id;
        if (CBIT_TEST(HopByHopHeadersMask, id)) {
            delAt(pos, headers_deleted);
            CBIT_CLR(mask, id);
        }
    }
}