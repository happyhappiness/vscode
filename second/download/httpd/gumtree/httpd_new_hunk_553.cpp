    apr_rfc822_date(dates, r->request_time);
    apr_table_setn(r->headers_out, "Date", dates);
    apr_table_setn(r->headers_out, "Server", ap_get_server_version());

    /* set content-type */
    if (dirlisting) {
        ap_set_content_type(r, "text/html; charset=ISO-8859-1");
    }
    else {
        if (r->content_type) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: Content-Type set to %s", r->content_type);
        }
