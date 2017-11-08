static int check_headers_table(apr_table_t *t, struct check_header_ctx *ctx)
{
    const apr_array_header_t *headers = apr_table_elts(t);
    apr_table_entry_t *header;
    int i;

    for (i = 0; i < headers->nelts; ++i) {
        header = &((apr_table_entry_t *)headers->elts)[i];
        if (!header->key) {
            continue;
        }
        if (!check_header(ctx, header->key, (const char **)&header->val)) {
            return 0;
        }
    }
    return 1;
}