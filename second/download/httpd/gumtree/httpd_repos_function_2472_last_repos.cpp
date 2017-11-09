static void set_basic_http_header(apr_table_t *headers, request_rec *r,
                                  apr_pool_t *pool)
{
    char *date = NULL;
    const char *proxy_date = NULL;
    const char *server = NULL;
    const char *us = ap_get_server_banner();
    
    /*
     * keep the set-by-proxy server and date headers, otherwise
     * generate a new server header / date header
     */
    if (r && r->proxyreq != PROXYREQ_NONE) {
        proxy_date = apr_table_get(r->headers_out, "Date");
        if (!proxy_date) {
            /*
             * proxy_date needs to be const. So use date for the creation of
             * our own Date header and pass it over to proxy_date later to
             * avoid a compiler warning.
             */
            date = apr_palloc(pool, APR_RFC822_DATE_LEN);
            ap_recent_rfc822_date(date, r->request_time);
        }
        server = apr_table_get(r->headers_out, "Server");
    }
    else {
        date = apr_palloc(pool, APR_RFC822_DATE_LEN);
        ap_recent_rfc822_date(date, r? r->request_time : apr_time_now());
    }
    
    apr_table_setn(headers, "Date", proxy_date ? proxy_date : date );
    if (r) {
        apr_table_unset(r->headers_out, "Date");
    }
    
    if (!server && *us) {
        server = us;
    }
    if (server) {
        apr_table_setn(headers, "Server", server);
        if (r) {
            apr_table_unset(r->headers_out, "Server");
        }
    }
}