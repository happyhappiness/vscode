apr_status_t apr_filepath_list_split_impl(apr_array_header_t **pathelts,
                                          const char *liststr,
                                          char separator,
                                          apr_pool_t *p)
{
    char *path, *part, *ptr;
    char separator_string[2] = { '\0', '\0' };
    apr_array_header_t *elts;
    int nelts;

    separator_string[0] = separator;
    /* Count the number of path elements. We know there'll be at least
       one even if path is an empty string. */
    path = apr_pstrdup(p, liststr);
    for (nelts = 0, ptr = path; ptr != NULL; ++nelts)
    {
        ptr = strchr(ptr, separator);
        if (ptr)
            ++ptr;
    }

    /* Split the path into the array. */
    elts = apr_array_make(p, nelts, sizeof(char*));
    while ((part = apr_strtok(path, separator_string, &ptr)) != NULL)
    {
        if (*part == '\0')      /* Ignore empty path components. */
            continue;

        *(char**)apr_array_push(elts) = part;
        path = NULL;            /* For the next call to apr_strtok */
    }

    *pathelts = elts;
    return APR_SUCCESS;
}