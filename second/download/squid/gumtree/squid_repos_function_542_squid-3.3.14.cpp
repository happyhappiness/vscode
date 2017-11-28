static int
lc_cmp(const char *s1, const char *s2)
{
    char c1, c2;

    while (*s1 && *s2) {
        if (xisupper(*s1))
            c1 = xtolower(*s1);
        else
            c1 = *s1;
        if (xisupper(*s2))
            c2 = xtolower(*s2);
        else
            c2 = *s2;
        if (c1 != c2)
            return ((c1 - c2) > 0 ? 1 : -1);
        s1++;
        s2++;
    }

    if (*s1)
        return -1;
    if (*s2)
        return 1;
    return 0;
}