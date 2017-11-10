static void pphrase_array_clear(apr_array_header_t *arr)
{
    if (arr->nelts > 0) {
        memset(arr->elts, 0, arr->elt_size * arr->nelts);
    }
    arr->nelts = 0;
}