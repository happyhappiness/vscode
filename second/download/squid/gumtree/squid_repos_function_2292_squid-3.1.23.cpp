HttpHdrCc *
httpHdrCcParseCreate(const String * str)
{
    HttpHdrCc *cc = httpHdrCcCreate();

    if (!httpHdrCcParseInit(cc, str)) {
        httpHdrCcDestroy(cc);
        cc = NULL;
    }

    return cc;
}