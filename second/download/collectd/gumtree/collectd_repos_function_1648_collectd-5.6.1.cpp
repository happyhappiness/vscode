static _Bool has_suffix (char const *str, char const *suffix)
{
    size_t str_len = strlen (str);
    size_t suffix_len = strlen (suffix);
    size_t offset;

    if (suffix_len > str_len)
        return 0;
    offset = str_len - suffix_len;

    if (strcmp (str + offset, suffix) == 0)
        return 1;

    return 0;
}