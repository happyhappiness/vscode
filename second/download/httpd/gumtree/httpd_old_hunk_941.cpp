    if (rr->status != HTTP_OK) {
	ap_destroy_sub_req(rr);
	return DECLINED;
    }
    ap_destroy_sub_req(rr);

    retcode = apr_file_open(&f, metafilename, APR_READ | APR_CREATE, APR_OS_DEFAULT, r->pool);
    if (retcode != APR_SUCCESS) {
	if (APR_STATUS_IS_ENOENT(retcode)) {
	    return DECLINED;
	}
	ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
	      "meta file permissions deny server access: %s", metafilename);
