    rp->request_config  = ap_create_request_config(c->pool);
    proxy_run_create_req(r, rp);

    return rp;
}

/*
 * Reads headers from a buffer and returns an array of headers.
 * Returns NULL on file error
 * This routine tries to deal with too long lines and continuation lines.
 *
 * Note: Currently the headers are passed through unmerged. This has to be
 * done so that headers which react badly to merging (such as Set-Cookie
 * headers, which contain commas within the date field) do not get stuffed
 * up.
 */
PROXY_DECLARE(apr_table_t *)ap_proxy_read_headers(request_rec *r, request_rec *rr, char *buffer, int size, conn_rec *c)
{
    apr_table_t *headers_out;
    int len;
    char *value, *end;
    char field[MAX_STRING_LEN];
    int saw_headers = 0;
    void *sconf = r->server->module_config;
    proxy_server_conf *psc;

    psc = (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);

    headers_out = apr_table_make(r->pool, 20);

    /*
     * Read header lines until we get the empty separator line, a read error,
     * the connection closes (EOF), or we timeout.
     */
    while ((len = ap_getline(buffer, size, rr, 1)) > 0) {

	if (!(value = strchr(buffer, ':'))) {     /* Find the colon separator */

	    /* We may encounter invalid headers, usually from buggy
	     * MS IIS servers, so we need to determine just how to handle
	     * them. We can either ignore them, assume that they mark the
	     * start-of-body (eg: a missing CRLF) or (the default) mark
	     * the headers as totally bogus and return a 500. The sole
	     * exception is an extra "HTTP/1.0 200, OK" line sprinkled
	     * in between the usual MIME headers, which is a favorite
	     * IIS bug.
	     */
	     /* XXX: The mask check is buggy if we ever see an HTTP/1.10 */

	    if (!apr_date_checkmask(buffer, "HTTP/#.# ###*")) {
		if (psc->badopt == bad_error) {
		    /* Nope, it wasn't even an extra HTTP header. Give up. */
		    return NULL;
		}
		else if (psc->badopt == bad_body) {
		    /* if we've already started loading headers_out, then
		     * return what we've accumulated so far, in the hopes
		     * that they are useful. Otherwise, we completely bail.
		     */
		    /* FIXME: We've already scarfed the supposed 1st line of
		     * the body, so the actual content may end up being bogus
		     * as well. If the content is HTML, we may be lucky.
		     */
		    if (saw_headers) {
			ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
			 "proxy: Starting body due to bogus non-header in headers "
			 "returned by %s (%s)", r->uri, r->method);
			return headers_out;
		    } else {
			 ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
			 "proxy: No HTTP headers "
			 "returned by %s (%s)", r->uri, r->method);
			return NULL;
		    }
		}
	    }
	    /* this is the psc->badopt == bad_ignore case */
	    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
			 "proxy: Ignoring bogus HTTP header "
			 "returned by %s (%s)", r->uri, r->method);
	    continue;
	}

        *value = '\0';
        ++value;
	/* XXX: RFC2068 defines only SP and HT as whitespace, this test is
	 * wrong... and so are many others probably.
	 */
        while (apr_isspace(*value))
            ++value;            /* Skip to start of value   */

	/* should strip trailing whitespace as well */
	for (end = &value[strlen(value)-1]; end > value && apr_isspace(*end); --end)
	    *end = '\0';

        /* make sure we add so as not to destroy duplicated headers */
        apr_table_add(headers_out, buffer, value);
        saw_headers = 1;

	/* the header was too long; at the least we should skip extra data */
	if (len >= size - 1) { 
	    while ((len = ap_getline(field, MAX_STRING_LEN, rr, 1))
		    >= MAX_STRING_LEN - 1) {
		/* soak up the extra data */
	    }
	    if (len == 0) /* time to exit the larger loop as well */
		break;
	}
    }
    return headers_out;
}


/*
 * list is a comma-separated list of case-insensitive tokens, with
 * optional whitespace around the tokens.
 * The return returns 1 if the token val is found in the list, or 0
 * otherwise.
