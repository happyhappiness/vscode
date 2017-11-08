static void prep_string(const char ** str, apr_pool_t *p)
{
    const char *ch = *str;
    char *ch2;
    apr_size_t widen = 0;

    if (!ch) {
        return;
    }
    while (*ch) {
        if (*(ch++) & 0x80) {
            ++widen;
        }
    }
    if (!widen) {
        return;
    }
    widen += (ch - *str) + 1;
    ch = *str;
    *str = ch2 = apr_palloc(p, widen);
    while (*ch) {
        if (*ch & 0x80) {
            /* sign extension won't hurt us here */
            *(ch2++) = 0xC0 | ((*ch >> 6) & 0x03);
            *(ch2++) = 0x80 | (*(ch++) & 0x3f);
        }
        else {
            *(ch2++) = *(ch++);
        }
    }
    *(ch2++) = '\0';
}