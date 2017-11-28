const char *
getStringPrefix(const char *str, const char *end)
{
#define SHORT_PREFIX_SIZE 512
    LOCAL_ARRAY(char, buf, SHORT_PREFIX_SIZE);
    const int sz = 1 + (end ? end - str : strlen(str));
    xstrncpy(buf, str, (sz > SHORT_PREFIX_SIZE) ? SHORT_PREFIX_SIZE : sz);
    return buf;
}