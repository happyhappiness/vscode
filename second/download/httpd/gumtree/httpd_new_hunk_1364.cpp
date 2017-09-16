                                    r->proxyreq ? "Proxy-Authorization"

                                    : "Authorization");

    int l;

    int s, vk = 0, vv = 0;

    const char *t;

    char *key, *value;

    const char *scheme;



    if (!(t = ap_auth_type(r)) || strcasecmp(t, "Digest"))

	return DECLINED;



    if (!ap_auth_name(r)) {

	ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,

		    "need AuthName: %s", r->uri);

	return SERVER_ERROR;

    }



    if (!auth_line) {

	ap_note_digest_auth_failure(r);

	return AUTH_REQUIRED;

    }



    if (strcasecmp(scheme=ap_getword(r->pool, &auth_line, ' '), "Digest")) {

	/* Client tried to authenticate using wrong auth scheme */

	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

		    "client used wrong authentication scheme: %s for %s", 

		    scheme, r->uri);

	ap_note_digest_auth_failure(r);

	return AUTH_REQUIRED;

    }



    l = strlen(auth_line);



