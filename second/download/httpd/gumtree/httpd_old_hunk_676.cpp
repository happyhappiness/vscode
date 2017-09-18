#if defined(USE_MDTM) && (defined(HAVE_TIMEGM) || defined(HAVE_GMTOFF))
    apr_time_t mtime = 0L;
#endif

    /* stuff for PASV mode */
    int connect = 0, use_port = 0;
    char dates[AP_RFC822_DATE_LEN];

    /* is this for us? */
    if (proxyhost) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: declining URL %s - proxyhost %s specified:", url, proxyhost);
        return DECLINED;        /* proxy connections are via HTTP */
