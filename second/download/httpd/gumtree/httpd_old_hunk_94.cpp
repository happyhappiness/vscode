PROXY_DECLARE(apr_table_t *)ap_proxy_read_headers(request_rec *r, request_rec *rr, char *buffer, int size, conn_rec *c)
{
    apr_table_t *headers_out;
    int len;
    char *value, *end;
    char field[MAX_STRING_LEN];

    headers_out = apr_table_make(r->pool, 20);

    /*
     * Read header lines until we get the empty separator line, a read error,
     * the connection closes (EOF), or we timeout.
     */
    while ((len = ap_getline(buffer, size, rr, 1)) > 0) {

	if (!(value = strchr(buffer, ':'))) {     /* Find the colon separator */

	    /* Buggy MS IIS servers sometimes return invalid headers
	     * (an extra "HTTP/1.0 200, OK" line sprinkled in between
	     * the usual MIME headers). Try to deal with it in a sensible
	     * way, but log the fact.
	     * XXX: The mask check is buggy if we ever see an HTTP/1.10 */

	    if (!apr_date_checkmask(buffer, "HTTP/#.# ###*")) {
		/* Nope, it wasn't even an extra HTTP header. Give up. */
		return NULL;
	    }

	    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
			 "proxy: Ignoring duplicate HTTP header "
			 "returned by %s (%s)", r->uri, r->method);
	    continue;
	}

        *value = '\0';
        ++value;
