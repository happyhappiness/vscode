     * either masking it with a <Location > directive or alias, or stowing
     * the file outside of the web document tree, while providing the
     * appropriate directory blocks to allow access to it as a file.
     */
    rr = ap_sub_req_lookup_file(metafilename, r, NULL);
    if (rr->status != HTTP_OK) {
    ap_destroy_sub_req(rr);
	return DECLINED;
    }
    ap_destroy_sub_req(rr);

    retcode = apr_file_open(&f, metafilename, APR_READ, APR_OS_DEFAULT, r->pool);
    if (retcode != APR_SUCCESS) {
	if (APR_STATUS_IS_ENOENT(retcode)) {
	    return DECLINED;
	}
	ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
            "meta file permissions deny server access: %s", metafilename);
	return HTTP_FORBIDDEN;
    };

    /* read the headers in */
    rv = scan_meta_file(r, f);
    apr_file_close(f);
