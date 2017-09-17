	else
	    ret = FORBIDDEN;
    }

    if (ret == FORBIDDEN
	&& (ap_satisfies(r) != SATISFY_ANY || !ap_some_auth_required(r))) {
	ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
		  "client denied by server configuration: %s",
		  r->filename);
    }

    return ret;
}


++ apache_1.3.2/src/modules/standard/mod_actions.c	1998-08-07 01:30:53.000000000 +0800
