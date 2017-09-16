

	errmsg = ap_srm_command_loop(&parms, dc);



	ap_cfg_closefile(f);



	if (errmsg) {

	    ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO, r->server, "%s: %s",

                        filename, errmsg);

            return HTTP_INTERNAL_SERVER_ERROR;

	}



	*result = dc;

    }

    else {

	if (errno == ENOENT || errno == ENOTDIR)

	    dc = NULL;

	else {

	    ap_log_error(APLOG_MARK, APLOG_CRIT, r->server,

			"%s pcfg_openfile: unable to check htaccess file, ensure it is readable",

			filename);

	    return HTTP_FORBIDDEN;

	}

    }



/* cache it */

    new = ap_palloc(r->pool, sizeof(struct htaccess_result));

