
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
