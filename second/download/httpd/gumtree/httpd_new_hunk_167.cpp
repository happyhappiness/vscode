    q = ap_palloc(p, 30);
    ap_snprintf(q, 30, "%s, %.2d %s %d %.2d:%.2d:%.2d GMT", ap_day_snames[wk], mday,
		ap_month_snames[mon], year, hour, min, sec);
    return q;
}


/* NOTE: This routine is taken from http_protocol::getline()
 * because the old code found in the proxy module was too
 * difficult to understand and maintain.
 */
/* Get a line of protocol input, including any continuation lines
 * caused by MIME folding (or broken clients) if fold != 0, and place it
 * in the buffer s, of size n bytes, without the ending newline.
 *
 * Returns -1 on error, or the length of s.
 *
 * Note: Because bgets uses 1 char for newline and 1 char for NUL,
 *       the most we can get is (n - 2) actual characters if it
 *       was ended by a newline, or (n - 1) characters if the line
 *       length exceeded (n - 1).  So, if the result == (n - 1),
 *       then the actual input line exceeded the buffer length,
 *       and it would be a good idea for the caller to puke 400 or 414.
 */
static int proxy_getline(char *s, int n, BUFF *in, int fold)
{
    char *pos, next;
    int retval;
    int total = 0;

    pos = s;

    do {
        retval = ap_bgets(pos, n, in);     /* retval == -1 if error, 0 if EOF */

        if (retval <= 0)
            return ((retval < 0) && (total == 0)) ? -1 : total;

        /* retval is the number of characters read, not including NUL      */

        n -= retval;            /* Keep track of how much of s is full     */
        pos += (retval - 1);    /* and where s ends                        */
        total += retval;        /* and how long s has become               */

        if (*pos == '\n') {     /* Did we get a full line of input?        */
            *pos = '\0';
            --total;
            ++n;
        }
        else
            return total;       /* if not, input line exceeded buffer size */

        /* Continue appending if line folding is desired and
         * the last line was not empty and we have room in the buffer and
         * the next line begins with a continuation character.
         */
    } while (fold && (retval != 1) && (n > 1)
                  && (ap_blookc(&next, in) == 1)
                  && ((next == ' ') || (next == '\t')));

    return total;
}


/*
 * Reads headers from a buffer and returns an array of headers.
 * Returns NULL on file error
 * This routine tries to deal with too long lines and continuation lines.
 * @@@: XXX: FIXME: currently the headers are passed thru un-merged. 
 * Is that okay, or should they be collapsed where possible?
 */
table *ap_proxy_read_headers(request_rec *r, char *buffer, int size, BUFF *f)
{
    table *resp_hdrs;
    int len;
    char *value, *end;
    char field[MAX_STRING_LEN];

    resp_hdrs = ap_make_table(r->pool, 20);

    /*
     * Read header lines until we get the empty separator line, a read error,
     * the connection closes (EOF), or we timeout.
     */
    while ((len = proxy_getline(buffer, size, f, 1)) > 0) {
	
	if (!(value = strchr(buffer, ':'))) {     /* Find the colon separator */

	    /* Buggy MS IIS servers sometimes return invalid headers
	     * (an extra "HTTP/1.0 200, OK" line sprinkled in between
	     * the usual MIME headers). Try to deal with it in a sensible
	     * way, but log the fact.
	     * XXX: The mask check is buggy if we ever see an HTTP/1.10 */

	    if (!ap_checkmask(buffer, "HTTP/#.# ###*")) {
		/* Nope, it wasn't even an extra HTTP header. Give up. */
		return NULL;
	    }

	    ap_log_error(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, r->server,
			 "proxy: Ignoring duplicate HTTP header "
			 "returned by %s (%s)", r->uri, r->method);
	    continue;
	}

        *value = '\0';
        ++value;
	/* XXX: RFC2068 defines only SP and HT as whitespace, this test is
	 * wrong... and so are many others probably.
	 */
        while (ap_isspace(*value))
            ++value;            /* Skip to start of value   */

	/* should strip trailing whitespace as well */
	for (end = &value[strlen(value)-1]; end > value && ap_isspace(*end); --end)
	    *end = '\0';

        ap_table_add(resp_hdrs, buffer, value);

	/* the header was too long; at the least we should skip extra data */
	if (len >= size - 1) { 
	    while ((len = proxy_getline(field, MAX_STRING_LEN, f, 1))
		    >= MAX_STRING_LEN - 1) {
		/* soak up the extra data */
	    }
	    if (len == 0) /* time to exit the larger loop as well */
		break;
	}
    }
    return resp_hdrs;
}

long int ap_proxy_send_fb(BUFF *f, request_rec *r, cache_req *c)
{
    int  ok = 1;
    char buf[IOBUFSIZE];
    long total_bytes_rcv;
    register int n, o, w;
    conn_rec *con = r->connection;
