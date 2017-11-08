apr_status_t h2_to_h1_add_headers(h2_to_h1 *to_h1, apr_table_t *headers)
{
    apr_table_do(set_header, to_h1, headers, NULL);
    return APR_SUCCESS;
}