bool
xstrtoul(const char *s, char **end, unsigned long *value,
         unsigned long min, unsigned long max)
{
    char *my_end = NULL;

    errno = 0;
    unsigned long v = strtoul(s, &my_end, 0);

    if (my_end == s)
        return false;
    if (end != NULL)
        *end = my_end;

    if (errno != ERANGE && min <= v && (max == 0 || v <= max)) {
        if (value != NULL)
            *value = v;
        if (end == NULL)
            return *my_end == '\0';
        return true;
    }

    return false;
}