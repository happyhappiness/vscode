HttpHdrSc *
HttpHeader::getSc() const
{
    if (!CBIT_TEST(mask, HDR_SURROGATE_CONTROL))
        return NULL;

    String s;

    (void) getList(HDR_SURROGATE_CONTROL, &s);

    HttpHdrSc *sc = httpHdrScParseCreate(s);

    ++ HttpHeaderStats[owner].ccParsedCount;

    if (sc)
        sc->updateStats(&HttpHeaderStats[owner].scTypeDistr);

    httpHeaderNoteParsedEntry(HDR_SURROGATE_CONTROL, s, !sc);

    return sc;
}