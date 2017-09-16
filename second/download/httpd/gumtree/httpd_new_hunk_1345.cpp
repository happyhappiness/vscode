		while (groups[0]) {

		    v = ap_getword(r->pool, &groups, ',');

		    if (!strcmp(v, w))

			return OK;

		}

	    }

	    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,

			"user %s not in right group: %s", user, r->filename);

	    ap_note_basic_auth_failure(r);

	    return AUTH_REQUIRED;

	}

    }



++ apache_1.3.2/src/modules/standard/mod_auth_dbm.c	1998-08-07 01:30:55.000000000 +0800

