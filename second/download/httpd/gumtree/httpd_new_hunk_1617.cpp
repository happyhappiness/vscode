        tag_val = get_tag(r->pool, in, tag, sizeof(tag), 0);
        if (*tag == '\0') {
            return 1;
        }
        else if (!strcmp(tag, "done")) {
	    if (expr == NULL) {
		ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
			    "missing expr in if statement: %s",
			    r->filename);
		ap_rputs(error, r);
		return 1;
	    }
            *printing = *conditional_status = parse_expr(r, expr, error);
