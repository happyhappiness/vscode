static apr_status_t store_table(apr_table_t *table, unsigned char *buffer,
        apr_size_t buffer_len, apr_size_t *slider)
{
    int i, len;
    apr_table_entry_t *elts;

    elts = (apr_table_entry_t *) apr_table_elts(table)->elts;
    for (i = 0; i < apr_table_elts(table)->nelts; ++i) {
        if (elts[i].key != NULL) {
            apr_size_t key_len = strlen(elts[i].key);
            apr_size_t val_len = strlen(elts[i].val);
            if (key_len + val_len + 5 >= buffer_len - *slider) {
                return APR_EOF;
            }
            len = apr_snprintf(buffer ? (char *) buffer + *slider : NULL,
                    buffer ? buffer_len - *slider : 0, "%s: %s" CRLF,
                    elts[i].key, elts[i].val);
            *slider += len;
        }
    }
    if (3 >= buffer_len - *slider) {
        return APR_EOF;
    }
    if (buffer) {
        memcpy(buffer + *slider, CRLF, sizeof(CRLF) - 1);
    }
    *slider += sizeof(CRLF) - 1;

    return APR_SUCCESS;
}