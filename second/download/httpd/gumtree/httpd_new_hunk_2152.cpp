    apr_rfc822_date(dates, r->request_time);
    apr_table_setn(r->headers_out, "Date", dates);
    apr_table_setn(r->headers_out, "Server", ap_get_server_banner());

    /* set content-type */
    if (dirlisting) {
        proxy_dir_conf *dconf = ap_get_module_config(r->per_dir_config,
                                                     &proxy_module);

        ap_set_content_type(r, apr_pstrcat(p, "text/html;charset=",
                                           dconf->ftp_directory_charset ?
                                           dconf->ftp_directory_charset :
                                           "ISO-8859-1",  NULL));
    }
    else {
        if (r->content_type) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: Content-Type set to %s", r->content_type);
        }
