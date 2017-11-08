static void extract_san_array(apr_table_t *t, const char *pfx,
                              apr_array_header_t *entries, apr_pool_t *p)
{
    int i;

    for (i = 0; i < entries->nelts; i++) {
        const char *key = apr_psprintf(p, "%s_%d", pfx, i);
        apr_table_setn(t, key, APR_ARRAY_IDX(entries, i, const char *));
    }
}