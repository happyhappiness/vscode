const char *
squid_strnstr(const char *s, const char *find, size_t slen)
{
    char c, sc;
    size_t len;

    if ((c = *find++) != '\0') {
        len = strlen(find);
        do {
            do {
                if (slen < 1 || (sc = *s) == '\0')
                    return (NULL);
                --slen;
                ++s;
            } while (sc != c);
            if (len > slen)
                return (NULL);
        } while (strncmp(s, find, len) != 0);
        --s;
    }
    return s;
}