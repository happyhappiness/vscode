char *h2_strlwr(char *s)
{
    char *p;
    for (p = s; *p; ++p) {
        if (*p >= 'A' && *p <= 'Z') {
            *p += 'a' - 'A';
        }
    }
    return s;
}