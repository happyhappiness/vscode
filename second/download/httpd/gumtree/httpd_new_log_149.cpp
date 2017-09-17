ap_log_rerror(APLOG_MARK, APLOG_INFO|APLOG_NOERRNO, r,
		      "proxy: missing or failed auth to %s",
		      ap_unparse_uri_components(r->pool,
		      &r->parsed_uri, UNP_OMITPATHINFO));