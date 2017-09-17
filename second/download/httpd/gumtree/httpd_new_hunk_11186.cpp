
    f = ap_pfopen(r->pool, metafilename, "r");
    if (f == NULL) {
	if (errno == ENOENT) {
	    return DECLINED;
	}
	ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
	      "meta file permissions deny server access: %s", metafilename);
	return FORBIDDEN;
    };

    /* read the headers in */
    rv = scan_meta_file(r, f);
++ apache_1.3.2/src/modules/standard/mod_cgi.c	1998-09-04 06:40:42.000000000 +0800
