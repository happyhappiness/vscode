    /* set content-type */
    if (dirlisting) {
        ap_set_content_type(r, "text/html");
    }
    else {
        if (r->content_type) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, r->server,
                     "proxy: FTP: Content-Type set to %s", r->content_type);
        }
        else {
            ap_set_content_type(r, ap_default_type(r));
        }
        if (xfer_type != 'A' && size != NULL) {
            /* We "trust" the ftp server to really serve (size) bytes... */
            apr_table_setn(r->headers_out, "Content-Length", size);
            ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, r->server,
                         "proxy: FTP: Content-Length set to %s", size);
        }
    }
    apr_table_setn(r->headers_out, "Content-Type", r->content_type);
    ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, r->server,
                 "proxy: FTP: Content-Type set to %s", r->content_type);

#if defined(USE_MDTM) && (defined(HAVE_TIMEGM) || defined(HAVE_GMTOFF))
    if (mtime != 0L) {
        char datestr[APR_RFC822_DATE_LEN];
        apr_rfc822_date(datestr, mtime);
        apr_table_set(r->headers_out, "Last-Modified", datestr);
        ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, r->server,
                 "proxy: FTP: Last-Modified set to %s", datestr);
    }
#endif /* USE_MDTM */

    /* If an encoding has been set by mistake, delete it.
     * @@@ FIXME (e.g., for ftp://user@host/file*.tar.gz,
