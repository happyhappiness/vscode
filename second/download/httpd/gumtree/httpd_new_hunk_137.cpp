	}
	ap_destroy_sub_req(pa_req);
    }
}


static int set_cookie_doo_doo(void *v, const char *key, const char *val)
{
    ap_table_addn(v, key, val);
    return 1;
}

API_EXPORT(int) ap_scan_script_header_err_core(request_rec *r, char *buffer,
				       int (*getsfunc) (char *, int, void *),
				       void *getsfunc_data)
{
    char x[MAX_STRING_LEN];
    char *w, *l;
    int p;
    int cgi_status = HTTP_OK;
    table *merge;
    table *cookie_table;

    if (buffer) {
	*buffer = '\0';
    }
    w = buffer ? buffer : x;

    ap_hard_timeout("read script header", r);

    /* temporary place to hold headers to merge in later */
    merge = ap_make_table(r->pool, 10);

    /* The HTTP specification says that it is legal to merge duplicate
     * headers into one.  Some browsers that support Cookies don't like
     * merged headers and prefer that each Set-Cookie header is sent
     * separately.  Lets humour those browsers by not merging.
     * Oh what a pain it is.
     */
    cookie_table = ap_make_table(r->pool, 2);
    ap_table_do(set_cookie_doo_doo, cookie_table, r->err_headers_out, "Set-Cookie", NULL);

    while (1) {

	if ((*getsfunc) (w, MAX_STRING_LEN - 1, getsfunc_data) == 0) {
	    ap_kill_timeout(r);
	    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
			  "Premature end of script headers: %s", r->filename);
	    ap_table_setn(r->notes, "error-notes",
			  "Premature end of script headers");
	    return HTTP_INTERNAL_SERVER_ERROR;
	}

	/* Delete terminal (CR?)LF */

	p = strlen(w);
	if (p > 0 && w[p - 1] == '\n') {
