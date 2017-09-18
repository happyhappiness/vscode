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
