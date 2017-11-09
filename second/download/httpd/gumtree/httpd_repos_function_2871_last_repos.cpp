h2_headers *h2_headers_die(apr_status_t type,
                             const h2_request *req, apr_pool_t *pool)
{
    h2_headers *headers;
    char *date;
    
    headers = apr_pcalloc(pool, sizeof(h2_headers));
    headers->status    = (type >= 200 && type < 600)? type : 500;
    headers->headers        = apr_table_make(pool, 5);
    headers->notes          = apr_table_make(pool, 5);

    date = apr_palloc(pool, APR_RFC822_DATE_LEN);
    ap_recent_rfc822_date(date, req? req->request_time : apr_time_now());
    apr_table_setn(headers->headers, "Date", date);
    apr_table_setn(headers->headers, "Server", ap_get_server_banner());
    
    return headers;
}