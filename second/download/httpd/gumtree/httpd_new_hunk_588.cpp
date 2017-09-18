    cookie_table = apr_table_make(r->pool, 2);
    apr_table_do(set_cookie_doo_doo, cookie_table, r->err_headers_out, "Set-Cookie", NULL);

    while (1) {

	if ((*getsfunc) (w, MAX_STRING_LEN - 1, getsfunc_data) == 0) {
	    ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_TOCLIENT, 0, r,
			  "Premature end of script headers: %s", 
                          apr_filename_of_pathname(r->filename));
	    return HTTP_INTERNAL_SERVER_ERROR;
	}

	/* Delete terminal (CR?)LF */
