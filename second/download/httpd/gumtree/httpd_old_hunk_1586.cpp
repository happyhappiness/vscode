	return res;

    if (!sec->pwfile)
	return DECLINED;

    if (!(a1 = get_hash(r, c->user, sec->pwfile))) {
	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
		    "user %s not found: %s", c->user, r->uri);
	ap_note_digest_auth_failure(r);
	return AUTH_REQUIRED;
    }
    if (strcmp(response->digest, find_digest(r, response, a1))) {
	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
		    "user %s: password mismatch: %s", c->user, r->uri);
	ap_note_digest_auth_failure(r);
	return AUTH_REQUIRED;
    }
    return OK;
}
