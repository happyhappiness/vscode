	ap_destroy_sub_req(pa_req);
    }
}


static int scan_script_header_err_core(request_rec *r, char *buffer,
		 int (*getsfunc) (char *, int, void *), void *getsfunc_data)
{
    char x[MAX_STRING_LEN];
    char *w, *l;
    int p;
    int cgi_status = HTTP_OK;

    if (buffer)
	*buffer = '\0';
    w = buffer ? buffer : x;

    ap_hard_timeout("read script header", r);

    while (1) {

	if ((*getsfunc) (w, MAX_STRING_LEN - 1, getsfunc_data) == 0) {
	    ap_kill_timeout(r);
	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
			"Premature end of script headers: %s", r->filename);
	    return SERVER_ERROR;
	}

	/* Delete terminal (CR?)LF */

	p = strlen(w);
	if (p > 0 && w[p - 1] == '\n') {
	    if (p > 1 && w[p - 2] == '\015')
		w[p - 2] = '\0';
	    else
		w[p - 1] = '\0';
	}

	/*
	 * If we've finished reading the headers, check to make sure any
	 * HTTP/1.1 conditions are met.  If so, we're done; normal processing
	 * will handle the script's output.  If not, just return the error.
