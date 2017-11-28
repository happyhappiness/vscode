HttpHdrCc *
HttpHeader::getCc() const
{
    if (!CBIT_TEST(mask, Http::HdrType::CACHE_CONTROL))
        return NULL;
    PROF_start(HttpHeader_getCc);

    String s;
    getList(Http::HdrType::CACHE_CONTROL, &s);

    HttpHdrCc *cc=new HttpHdrCc();

    if (!cc->parse(s)) {
        delete cc;
        cc = NULL;
    }

    ++ HttpHeaderStats[owner].ccParsedCount;

    if (cc)
        httpHdrCcUpdateStats(cc, &HttpHeaderStats[owner].ccTypeDistr);

    httpHeaderNoteParsedEntry(Http::HdrType::CACHE_CONTROL, s, !cc);

    PROF_stop(HttpHeader_getCc);

    return cc;
}