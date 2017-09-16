

    f = ap_pfopen(r->pool, metafilename, "r");

    if (f == NULL) {

	if (errno == ENOENT) {

	    return DECLINED;

	}

	ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

	      "meta file permissions deny server access: %s", metafilename);

	return FORBIDDEN;

    };



    /* read the headers in */

    rv = scan_meta_file(r, f);

-- apache_1.3.1/src/modules/standard/mod_cgi.c	1998-06-28 02:09:31.000000000 +0800

