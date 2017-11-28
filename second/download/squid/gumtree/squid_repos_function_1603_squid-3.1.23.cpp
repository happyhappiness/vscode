HttpHdrSc *
httpHdrScParseCreate(const String * str)
{
    HttpHdrSc *sc = httpHdrScCreate();

    if (!httpHdrScParseInit(sc, str)) {
        httpHdrScDestroy(sc);
        sc = NULL;
    }

    return sc;
}