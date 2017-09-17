    const char *location;

    r->allowed |= (1 << M_GET);
    if (r->method_number != M_GET)
	return DECLINED;
    if (r->finfo.st_mode == 0) {
	ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
		    "File does not exist: %s", r->filename);
	return NOT_FOUND;
    }

    f = ap_pfopen(r->pool, r->filename, "r");

    if (f == NULL) {
	ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
		    "file permissions deny server access: %s", r->filename);
	return FORBIDDEN;
    }

    scan_script_header(r, f);
    location = ap_table_get(r->headers_out, "Location");

    if (location && location[0] == '/' &&
	((r->status == HTTP_OK) || ap_is_HTTP_REDIRECT(r->status))) {

	ap_pfclose(r->pool, f);

	/* Internal redirect -- fake-up a pseudo-request */
	r->status = HTTP_OK;

