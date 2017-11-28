bool
xstrtoul(const char *s, char **end, unsigned long *value,
         unsigned long min, unsigned long max)
{
    unsigned long v;
    char *my_end;

    errno = 0;
    v = strtoul(s, &my_end, 0);

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