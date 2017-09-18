	    const char *orig_groups, *groups;
	    char *v;

	    if (!(groups = get_db_grp(r, user, sec->auth_dbgrpfile))) {
		if (!(sec->auth_dbauthoritative))
		    return DECLINED;
		ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
			    "user %s not in DB group file %s: %s",
			    user, sec->auth_dbgrpfile, r->filename);
		ap_note_basic_auth_failure(r);
		return AUTH_REQUIRED;
	    }
	    orig_groups = groups;
