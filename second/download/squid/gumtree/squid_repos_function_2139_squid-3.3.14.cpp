inline const char*
RequestMethodStr(const _method_t m)
{
    return HttpRequestMethod(m).image();
}