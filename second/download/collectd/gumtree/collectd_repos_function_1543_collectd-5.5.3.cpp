static size_t count_parts (char const *key)
{
    char const *ptr;
    size_t parts_num = 0;

    for (ptr = key; ptr != NULL; ptr = strchr (ptr + 1, '.'))
        parts_num++;

    return parts_num;
}