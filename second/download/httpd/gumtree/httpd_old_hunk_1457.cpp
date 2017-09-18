{
    const char *auth_line = ap_table_get(r->headers_in,
                                    r->proxyreq ? "Proxy-Authorization"
                                    : "Authorization");
    int l;
    int s, vk = 0, vv = 0;
    char *t, *key, *value;

    if (!(t = ap_auth_type(r)) || strcasecmp(t, "Digest"))
	return DECLINED;

    if (!ap_auth_name(r)) {
	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
