

    /* Second, check for actions (which override the method scripts) */

    if ((t = ap_table_get(conf->action_types,

		       action ? action : ap_default_type(r)))) {

	script = t;

	if (r->finfo.st_mode == 0) {

	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

			"File does not exist: %s", r->filename);

	    return NOT_FOUND;

	}

    }



    if (script == NULL)

-- apache_1.3.1/src/modules/standard/mod_alias.c	1998-07-09 01:47:13.000000000 +0800

