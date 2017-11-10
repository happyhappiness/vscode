static void *apr_array_push_noclear(apr_array_header_t *arr)
{
    if (arr->nelts == arr->nalloc) {
        int new_size = (arr->nalloc <= 0) ? 1 : arr->nalloc * 2;
        char *new_data;

        new_data = apr_palloc(arr->pool, arr->elt_size * new_size);

        memcpy(new_data, arr->elts, arr->nalloc * arr->elt_size);
        arr->elts = new_data;
        arr->nalloc = new_size;
    }

    ++arr->nelts;
    return arr->elts + (arr->elt_size * (arr->nelts - 1));
}