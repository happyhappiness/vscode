int strncasecmp(const char *a, const char *b, size_t n)
{
    const char *p = a;
    const char *q = b;

    for (p = a, q = b; /*NOTHING */ ; p++, q++) {
        int diff;
        if (p == a + n)
            return 0;           /*   Match up to n characters */
        if (!(*p && *q))
            return *p - *q;
        diff = apr_tolower(*p) - apr_tolower(*q);
        if (diff)
            return diff;
    }
    /*NOTREACHED */
}