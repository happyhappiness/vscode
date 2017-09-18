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
