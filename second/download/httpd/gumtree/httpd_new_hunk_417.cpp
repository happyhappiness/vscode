		ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

			    "ISA sent invalid headers", r->filename);

		return FALSE;

	    }



	    *value++ = '\0';

	    while (*value && ap_isspace(*value)) ++value;



	    /* Check all the special-case headers. Similar to what

	     * scan_script_header() does (see that function for

	     * more detail)

	     */



	    if (!strcasecmp(data, "Content-Type")) {

		char *tmp;

		/* Nuke trailing whitespace */

		

		char *endp = value + strlen(value) - 1;

		while (endp > value && ap_isspace(*endp)) *endp-- = '\0';

            

		tmp = ap_pstrdup (r->pool, value);

		ap_str_tolower(tmp);

		r->content_type = tmp;

	    }

	    else if (!strcasecmp(data, "Content-Length")) {

		ap_table_set(r->headers_out, data, value);

	    }

	    else if (!strcasecmp(data, "Transfer-Encoding")) {

		ap_table_set(r->headers_out, data, value);

++ apache_1.3.1/src/os/win32/multithread.c	1998-07-13 19:32:51.000000000 +0800

