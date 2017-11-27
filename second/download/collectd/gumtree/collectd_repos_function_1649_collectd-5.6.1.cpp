static size_t count_parts (char const *key)
{
    size_t parts_num = 0;

    for (const char *ptr = key; ptr != NULL; ptr = strchr (ptr + 1, '.'))
        parts_num++;

    return parts_num;
}