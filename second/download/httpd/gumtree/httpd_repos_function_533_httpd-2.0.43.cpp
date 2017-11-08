static int add_expires(request_rec *r)
{
    expires_dir_config *conf;
    char *code;
    apr_time_t base;
    apr_time_t additional;
    apr_time_t expires;
    int additional_sec;
    char *timestr;

    if (ap_is_HTTP_ERROR(r->status))       /* Don't add Expires headers to errors */
        return DECLINED;

    if (r->main != NULL)        /* Say no to subrequests */
        return DECLINED;

    conf = (expires_dir_config *) ap_get_module_config(r->per_dir_config, &expires_module);
    if (conf == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    "internal error: %s", r->filename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    if (conf->active != ACTIVE_ON)
        return DECLINED;

    /* we perhaps could use the default_type(r) in its place but that
     * may be 2nd guesing the desired configuration...  calling table_get
     * with a NULL key will SEGV us
     *
     * I still don't know *why* r->content_type would ever be NULL, this
     * is possibly a result of fixups being called in many different
     * places.  Fixups is probably the wrong place to be doing all this
     * work...  Bah.
     *
     * Changed as of 08.Jun.96 don't DECLINE, look for an ExpiresDefault.
     */
    if (r->content_type == NULL)
        code = NULL;
    else
        code = (char *) apr_table_get(conf->expiresbytype, 
		ap_field_noparam(r->pool, r->content_type));

    if (code == NULL) {
        /* no expires defined for that type, is there a default? */
        code = conf->expiresdefault;

        if (code[0] == '\0')
            return OK;
    }

    /* we have our code */

    switch (code[0]) {
    case 'M':
	if (r->finfo.filetype == 0) { 
	    /* file doesn't exist on disk, so we can't do anything based on
	     * modification time.  Note that this does _not_ log an error.
	     */
	    return DECLINED;
	}
	base = r->finfo.mtime;
        additional_sec = atoi(&code[1]);
        additional = apr_time_from_sec(additional_sec);
        break;
    case 'A':
        /* there's been some discussion and it's possible that 
         * 'access time' will be stored in request structure
         */
        base = r->request_time;
        additional_sec = atoi(&code[1]);
        additional = apr_time_from_sec(additional_sec);
        break;
    default:
        /* expecting the add_* routines to be case-hardened this 
         * is just a reminder that module is beta
         */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    "internal error: bad expires code: %s", r->filename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    expires = base + additional;
    apr_table_mergen(r->headers_out, "Cache-Control",
		    apr_psprintf(r->pool, "max-age=%" APR_TIME_T_FMT,
                                 apr_time_sec(expires - r->request_time)));
    timestr = apr_palloc(r->pool, APR_RFC822_DATE_LEN);
    apr_rfc822_date(timestr, expires);
    apr_table_setn(r->headers_out, "Expires", timestr);
    return OK;
}