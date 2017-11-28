char *
xstrncpy(char *dst, const char *src, size_t n)
{
    char *r = dst;

    if (!n || !dst)
        return dst;

    if (src)
        while (--n != 0 && *src != '\0') {
            *dst = *src;
            ++dst;
            ++src;
        }

    *dst = '\0';
    return r;
}