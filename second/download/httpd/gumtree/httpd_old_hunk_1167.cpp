        return errstatus;

    }



    r->allowed |= (1 << M_GET) | (1 << M_OPTIONS);



    if (r->method_number == M_INVALID) {

	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

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

	ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, r->server, 

                    "File does not exist: %s", 

		     r->path_info 

		         ? ap_pstrcat(r->pool, r->filename, r->path_info, NULL)

		         : r->filename);

	return NOT_FOUND;

    }

    if (r->method_number != M_GET) {

        return METHOD_NOT_ALLOWED;

    }

	

#if defined(__EMX__) || defined(WIN32)

    /* Need binary mode for OS/2 */

    f = ap_pfopen(r->pool, r->filename, "rb");

#else

    f = ap_pfopen(r->pool, r->filename, "r");

#endif



    if (f == NULL) {

        ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

		     "file permissions deny server access: %s", r->filename);

        return FORBIDDEN;

    }

	

    ap_update_mtime(r, r->finfo.st_mtime);

    ap_set_last_modified(r);

