static const char *zap_sp(const char *s)
{
    if (s == NULL) {
        return (NULL);
    }
    if (*s == '\0') {
        return (s);
    }

    /* skip prefixed white space */
    for (; *s == ' ' || *s == '\t' || *s == '\n'; s++)
        ;

    return (s);
}