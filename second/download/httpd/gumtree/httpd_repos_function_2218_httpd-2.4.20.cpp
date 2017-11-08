h2_response *h2_response_create(int stream_id,
                                int rst_error,
                                int http_status,
                                apr_array_header_t *hlines,
                                apr_table_t *notes,
                                apr_pool_t *pool)
{
    return h2_response_create_int(stream_id, rst_error, http_status,
                                  parse_headers(hlines, pool), notes, pool);
}