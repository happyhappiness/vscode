ap_log_rerror(APLOG_MARK, APLOG_INFO|APLOG_NOERRNO, r,
		"Domain missing: %s sent to %s%s%s", r->uri,
		ap_unparse_uri_components(r->pool, &r->parsed_uri,
		      UNP_OMITUSERINFO),
		ref ? " from " : "", ref ? ref : "");