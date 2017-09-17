				     domain, NULL);
    nuri = ap_unparse_uri_components(r->pool,
				  &r->parsed_uri,
				  UNP_REVEALPASSWORD);

    ap_table_set(r->headers_out, "Location", nuri);
    ap_log_error(APLOG_MARK, APLOG_INFO|APLOG_NOERRNO, r->server,
		"Domain missing: %s sent to %s%s%s", r->uri,
		ap_unparse_uri_components(r->pool, &r->parsed_uri,
		      UNP_OMITUSERINFO),
		ref ? " from " : "", ref ? ref : "");

    return HTTP_MOVED_PERMANENTLY;
