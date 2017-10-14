ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                "map file %s, line %d syntax error: requires at "
                "least two fields", r->uri, imap->line_number);