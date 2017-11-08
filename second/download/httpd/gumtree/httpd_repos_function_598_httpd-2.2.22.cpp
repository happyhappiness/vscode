static char *pphrase_array_get(apr_array_header_t *arr, int idx)
{
    if ((idx < 0) || (idx >= arr->nelts)) {
        return NULL;
    }

    return ((char **)arr->elts)[idx];
}