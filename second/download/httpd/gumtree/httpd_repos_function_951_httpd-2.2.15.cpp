static apr_table_t *deep_table_copy(apr_pool_t *p, const apr_table_t *table)
{
    const apr_array_header_t *array = apr_table_elts(table);
    apr_table_entry_t *elts = (apr_table_entry_t *) array->elts;
    apr_table_t *copy = apr_table_make(p, array->nelts);
    int i;

    for (i = 0; i < array->nelts; i++) {
        if (elts[i].key) {  
            apr_table_add(copy, elts[i].key, elts[i].val);
        }
    }

    return copy;
}