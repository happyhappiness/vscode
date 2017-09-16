        return errstatus;

    }



    r->allowed |= (1 << M_GET) | (1 << M_OPTIONS);



    if (r->method_number == M_INVALID) {

	ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,

		    "Invalid method in request %s", r->the_request);

	return NOT_IMPLEMENTED;

    }

    if (r->method_number == M_OPTIONS) {

        return ap_send_http_options(r);

    }

    if (r->method_number == M_PUT) {

        return METHOD_NOT_ALLOWED;

    }



    if (r->finfo.st_mode == 0 || (r->path_info && *r->path_info)) {

	char *emsg;



	emsg = "File does not exist: ";

	if (r->path_info == NULL) {

	    emsg = ap_pstrcat(r->pool, emsg, r->filename, NULL);

	}

	else {

	    emsg = ap_pstrcat(r->pool, emsg, r->filename, r->path_info, NULL);

	}

	ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, r, emsg);

	ap_table_setn(r->notes, "error-notes", emsg);

	return HTTP_NOT_FOUND;

    }

    if (r->method_number != M_GET) {

        return METHOD_NOT_ALLOWED;

    }

	

#if defined(OS2) || defined(WIN32)

    /* Need binary mode for OS/2 */

    f = ap_pfopen(r->pool, r->filename, "rb");

#else

    f = ap_pfopen(r->pool, r->filename, "r");

#endif



    if (f == NULL) {

        ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

		     "file permissions deny server access: %s", r->filename);

        return FORBIDDEN;

    }

	

    ap_update_mtime(r, r->finfo.st_mtime);

    ap_set_last_modified(r);

