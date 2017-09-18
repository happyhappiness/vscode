	return DECLINED;

    r->allowed |= (AP_METHOD_BIT << M_GET);
    if (r->method_number != M_GET)
	return DECLINED;
    if (r->finfo.filetype == 0) {
	ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
		    "File does not exist: %s", r->filename);
	return HTTP_NOT_FOUND;
    }

    if ((rv = apr_file_open(&f, r->filename, APR_READ, 
                APR_OS_DEFAULT, r->pool)) != APR_SUCCESS) {
