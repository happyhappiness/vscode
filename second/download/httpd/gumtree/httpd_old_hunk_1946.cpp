    const char *location;



    r->allowed |= (1 << M_GET);

    if (r->method_number != M_GET)

	return DECLINED;

    if (r->finfo.st_mode == 0) {

	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

		    "File does not exist: %s", r->filename);

	return NOT_FOUND;

    }



    f = ap_pfopen(r->pool, r->filename, "r");



    if (f == NULL) {

	ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

		    "file permissions deny server access: %s", r->filename);

	return FORBIDDEN;

    }



    scan_script_header(r, f);

    location = ap_table_get(r->headers_out, "Location");



    if (location && location[0] == '/' &&

	((r->status == HTTP_OK) || is_HTTP_REDIRECT(r->status))) {



	ap_pfclose(r->pool, f);



	/* Internal redirect -- fake-up a pseudo-request */

	r->status = HTTP_OK;



-- apache_1.3.1/src/modules/standard/mod_auth_anon.c	1998-07-04 06:08:49.000000000 +0800

