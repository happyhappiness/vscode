char *
strsep (char **stringp, const char *delim)
{
    char *start = *stringp;
    char *ptr;

    if (!start)
        return NULL;

    if (!*delim)
        ptr = start + strlen (start);
    else {
        ptr = strpbrk (start, delim);
        if (!ptr) {
            *stringp = NULL;
            return start;
        }
    }

    *ptr = '\0';
    *stringp = ptr + 1;

    return start;
}