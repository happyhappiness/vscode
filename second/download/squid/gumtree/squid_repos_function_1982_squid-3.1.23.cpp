HttpHdrContRange *
httpHdrContRangeParseCreate(const char *str)
{
    HttpHdrContRange *r = httpHdrContRangeCreate();

    if (!httpHdrContRangeParseInit(r, str)) {
        httpHdrContRangeDestroy(r);
        r = NULL;
    }

    return r;
}