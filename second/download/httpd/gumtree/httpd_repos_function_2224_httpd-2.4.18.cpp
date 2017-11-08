h2_response *h2_response_die(int stream_id, apr_status_t type,
                             const struct h2_request *req, apr_pool_t *pool)
{
    apr_table_t *headers = apr_table_make(pool, 5);
    char *date = NULL;
    
    date = apr_palloc(pool, APR_RFC822_DATE_LEN);
    ap_recent_rfc822_date(date, req->request_time);
    apr_table_setn(headers, "Date", date);
    apr_table_setn(headers, "Server", ap_get_server_banner());
    
    return h2_response_create_int(stream_id, 0, 500, headers, pool);
}