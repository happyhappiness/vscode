HttpHdrCc *
HttpHeader::getCc() const
{
    HttpHdrCc *cc;
    String s;

    if (!CBIT_TEST(mask, HDR_CACHE_CONTROL))
        return NULL;
    PROF_start(HttpHeader_getCc);

    getList(HDR_CACHE_CONTROL, &s);

    cc = httpHdrCcParseCreate(&s);

    HttpHeaderStats[owner].ccParsedCount++;

    if (cc)
        httpHdrCcUpdateStats(cc, &HttpHeaderStats[owner].ccTypeDistr);

    httpHeaderNoteParsedEntry(HDR_CACHE_CONTROL, s, !cc);

    PROF_stop(HttpHeader_getCc);

    return cc;
}