		while (groups[0]) {
		    v = ap_getword(r->pool, &groups, ',');
		    if (!strcmp(v, w))
			return OK;
		}
	    }
	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
			"user %s not in right group: %s",
			user, r->filename);
	    ap_note_basic_auth_failure(r);
	    return AUTH_REQUIRED;
	}
    }
-- apache_1.3.1/src/modules/standard/mod_autoindex.c	1998-07-09 01:47:14.000000000 +0800
