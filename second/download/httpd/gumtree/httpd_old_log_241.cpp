ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
		"map file %s, line %d syntax error: requires at "
                "least two fields", r->uri, imap->line_number);