
    /*
     * keep the set-by-proxy server and date headers, otherwise
     * generate a new server header / date header
     */
    if (r->proxyreq != PROXYREQ_NONE) {
        const char *proxy_date;

        proxy_date = apr_table_get(r->headers_out, "Date");
        if (!proxy_date) {
            /*
             * proxy_date needs to be const. So use date for the creation of
             * our own Date header and pass it over to proxy_date later to
             * avoid a compiler warning.
             */
            date = apr_palloc(r->pool, APR_RFC822_DATE_LEN);
            ap_recent_rfc822_date(date, r->request_time);
            proxy_date = date;
        }
        form_header_field(&h, "Date", proxy_date);
        server = apr_table_get(r->headers_out, "Server");
        if (server) {
            form_header_field(&h, "Server", server);
        } else {
            if (*us) {
                form_header_field(&h, "Server", ap_get_server_banner());
            }
        }
    }
    else {
        date = apr_palloc(r->pool, APR_RFC822_DATE_LEN);
        ap_recent_rfc822_date(date, r->request_time);
        form_header_field(&h, "Date", date);
        if (*us) {
            form_header_field(&h, "Server", ap_get_server_banner());
        }
    }

    /* unset so we don't send them again */
    apr_table_unset(r->headers_out, "Date");        /* Avoid bogosity */
    if (*us) {
        apr_table_unset(r->headers_out, "Server");
    }
}

AP_DECLARE(void) ap_basic_http_header(request_rec *r, apr_bucket_brigade *bb)
{
