
    r->status = HTTP_OK;
    r->status_line = "200 OK";

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
        else {
            ap_set_content_type(r, ap_default_type(r));
        }
        if (xfer_type != 'A' && size != NULL) {
            /* We "trust" the ftp server to really serve (size) bytes... */
            apr_table_setn(r->headers_out, "Content-Length", size);
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: FTP: Content-Length set to %s", size);
        }
    }
    apr_table_setn(r->headers_out, "Content-Type", r->content_type);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: FTP: Content-Type set to %s", r->content_type);

#if defined(USE_MDTM) && (defined(HAVE_TIMEGM) || defined(HAVE_GMTOFF))
    if (mtime != 0L) {
        char datestr[APR_RFC822_DATE_LEN];
        apr_rfc822_date(datestr, mtime);
        apr_table_set(r->headers_out, "Last-Modified", datestr);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: FTP: Last-Modified set to %s", datestr);
    }
#endif /* USE_MDTM */

    /* If an encoding has been set by mistake, delete it.
     * @@@ FIXME (e.g., for ftp://user@host/file*.tar.gz,
     * @@@        the encoding is currently set to x-gzip)
     */
    if (dirlisting && r->content_encoding != NULL)
        r->content_encoding = NULL;

    /* set content-encoding (not for dir listings, they are uncompressed)*/
    if (r->content_encoding != NULL && r->content_encoding[0] != '\0') {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
             "proxy: FTP: Content-Encoding set to %s", r->content_encoding);
        apr_table_setn(r->headers_out, "Content-Encoding", r->content_encoding);
    }

    /* wait for connection */
    if (use_port) {
        for (;;) {
