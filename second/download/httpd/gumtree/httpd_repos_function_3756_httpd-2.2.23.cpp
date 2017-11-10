void *memchr(const void *s, int c, size_t n)
{
    const char *cp;

    for (cp = s; n > 0; n--, cp++) {
        if (*cp == c)
            return (char *) cp; /* Casting away the const here */
    }

    return NULL;
}