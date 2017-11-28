HttpHdrSc *
HttpHeader::getSc() const
{
    if (!CBIT_TEST(mask, Http::HdrType::SURROGATE_CONTROL))
        return NULL;

    String s;

    (void) getList(Http::HdrType::SURROGATE_CONTROL, &s);

    HttpHdrSc *sc = httpHdrScParseCreate(s);

    ++ HttpHeaderStats[owner].ccParsedCount;

    if (sc)
        sc->updateStats(&HttpHeaderStats[owner].scTypeDistr);

    httpHeaderNoteParsedEntry(Http::HdrType::SURROGATE_CONTROL, s, !sc);

    return sc;
}