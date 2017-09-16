    magic_req_rec *req_dat = (magic_req_rec *)

		    ap_get_module_config(r->request_config, &mime_magic_module);

    magic_rsl *rsl;



    /* make sure we have a list to put it in */

    if (!req_dat) {

	ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, r->server,

		    MODNAME ": request config should not be NULL");

	if (!(req_dat = magic_set_config(r))) {

	    /* failure */

	    return -1;

	}

    }

