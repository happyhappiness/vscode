 * and OPTIONS at this point... anyone who wants to write a generic

 * handler for PUT or POST is free to do so, but it seems unwise to provide

 * any defaults yet... So, for now, we assume that this will always be

 * the last handler called and return 405 or 501.

 */



static int default_handler (request_rec *r)

{

    core_dir_config *d =

      (core_dir_config *)ap_get_module_config(r->per_dir_config, &core_module);

    int rangestatus, errstatus;

    FILE *f;

#ifdef USE_MMAP_FILES

    caddr_t mm;

#endif



    if (r->handler) {

	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING,

	    r->server, "handler \"%s\" not found, using default "

	    "handler for: %s", r->handler, r->filename);

    }



    /* This handler has no use for a request body (yet), but we still

     * need to read and discard it if the client sent one.

     */

    if ((errstatus = ap_discard_request_body(r)) != OK)

        return errstatus;



    r->allowed |= (1 << M_GET) | (1 << M_OPTIONS);



    if (r->method_number == M_INVALID) {

	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

		    "Invalid method in request %s", r->the_request);

	return NOT_IMPLEMENTED;

    }

    if (r->method_number == M_OPTIONS) return ap_send_http_options(r);

    if (r->method_number == M_PUT) return METHOD_NOT_ALLOWED;



    if (r->finfo.st_mode == 0 || (r->path_info && *r->path_info)) {

	ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, r->server, 

                    "File does not exist: %s", r->path_info ? 

                    ap_pstrcat(r->pool, r->filename, r->path_info, NULL)

		    : r->filename);

	return NOT_FOUND;

    }

    if (r->method_number != M_GET) return METHOD_NOT_ALLOWED;

	

#if defined(__EMX__) || defined(WIN32)

    /* Need binary mode for OS/2 */

    f = ap_pfopen (r->pool, r->filename, "rb");

#else

    f = ap_pfopen (r->pool, r->filename, "r");

#endif



    if (f == NULL) {

        ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

		    "file permissions deny server access: %s", r->filename);

        return FORBIDDEN;

    }

	

    ap_update_mtime (r, r->finfo.st_mtime);

    ap_set_last_modified(r);

    ap_set_etag(r);

    ap_table_setn(r->headers_out, "Accept-Ranges", "bytes");

    if (((errstatus = ap_meets_conditions(r)) != OK)

	|| (errstatus = ap_set_content_length (r, r->finfo.st_size))) {

	    return errstatus;

    }



#ifdef USE_MMAP_FILES

    ap_block_alarms();

    if ((r->finfo.st_size >= MMAP_THRESHOLD)

	&& ( !r->header_only || (d->content_md5 & 1))) {

	/* we need to protect ourselves in case we die while we've got the

 	 * file mmapped */

	mm = mmap (NULL, r->finfo.st_size, PROT_READ, MAP_PRIVATE,

		    fileno(f), 0);

	if (mm == (caddr_t)-1) {

	    ap_log_error(APLOG_MARK, APLOG_CRIT, r->server,

			"default_handler: mmap failed: %s", r->filename);

	}

    } else {

	mm = (caddr_t)-1;

    }



    if (mm == (caddr_t)-1) {

	ap_unblock_alarms();

#endif



	if (d->content_md5 & 1) {

	    ap_table_setn(r->headers_out, "Content-MD5", ap_md5digest(r->pool, f));

	}



	rangestatus = ap_set_byterange(r);

#ifdef CHARSET_EBCDIC

	/* To make serving of "raw ASCII text" files easy (they serve faster 

	 * since they don't have to be converted from EBCDIC), a new

