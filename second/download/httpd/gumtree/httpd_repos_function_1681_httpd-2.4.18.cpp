static int number_of_escapes(const char delim, const char *str)
{
    int nesc = 0;
    const char *s = str;
    while (*s) {
        if (*s == ESCAPE || *s == delim)
            nesc++;
        s++;
    }
    debug(fprintf(stderr, "escapes: %d ---%s---\n", nesc, str));
    return nesc;
}