HttpHdrContRange *
httpHdrContRangeParseCreate(const char *str)
{
    HttpHdrContRange *r = httpHdrContRangeCreate();

    if (!httpHdrContRangeParseInit(r, str)) {
        delete r;
        return nullptr;
    }

    return r;
}