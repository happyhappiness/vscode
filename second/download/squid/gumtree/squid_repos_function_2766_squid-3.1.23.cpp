void
HttpHeader::putWarning(const int code, const char *const text)
{
    char buf[512];
    snprintf(buf, sizeof(buf), "%i %s \"%s\"", code, visible_appname_string, text);
    putStr(HDR_WARNING, buf);
}