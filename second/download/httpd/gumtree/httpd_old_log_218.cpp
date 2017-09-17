r(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
			"user %s not in right group: %s",
			user, r->filename);