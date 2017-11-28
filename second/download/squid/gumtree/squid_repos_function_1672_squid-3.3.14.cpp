HttpHdrSc *
httpHdrScParseCreate(const String & str)
{
    HttpHdrSc *sc = new HttpHdrSc();

    if (!sc->parse(&str)) {
        delete sc;
        sc = NULL;
    }

    return sc;
}