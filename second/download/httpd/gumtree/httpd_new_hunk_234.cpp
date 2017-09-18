    apr_uri_t uri;
    const char *connectname;
    int connectport = 0;

    /* is this for us? */
    if (r->method_number != M_CONNECT) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
		     "proxy: CONNECT: declining URL %s", url);
	return DECLINED;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
		 "proxy: CONNECT: serving URL %s", url);


    /*
     * Step One: Determine Who To Connect To
     *
