    char *size = NULL;
    char xfer_type = 'A'; /* after ftp login, the default is ASCII */
    int  dirlisting = 0;
#if defined(USE_MDTM) && (defined(HAVE_TIMEGM) || defined(HAVE_GMTOFF))
    apr_time_t mtime = 0L;
#endif
    proxy_ftp_dir_conf *fdconf = ap_get_module_config(r->per_dir_config,
                                                      &proxy_ftp_module);

    /* stuff for PASV mode */
    int connect = 0, use_port = 0;
    char dates[APR_RFC822_DATE_LEN];
    int status;
    apr_pool_t *address_pool;

    /* is this for us? */
    if (proxyhost) {
        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, r->server,
                     "proxy: FTP: declining URL %s - proxyhost %s specified:", url, proxyhost);
        return DECLINED;        /* proxy connections are via HTTP */
    }
    if (strncasecmp(url, "ftp:", 4)) {
        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, r->server,
                     "proxy: FTP: declining URL %s - not ftp:", url);
        return DECLINED;        /* only interested in FTP */
    }
    ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, r->server,
                 "proxy: FTP: serving URL %s", url);


    /*
     * I: Who Do I Connect To? -----------------------
     *
