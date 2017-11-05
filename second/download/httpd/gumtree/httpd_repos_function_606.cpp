static int set_expiration_fields(request_rec *r, const char *code,
                                 apr_table_t *t)
{
    apr_time_t base;
    apr_time_t additional;
    apr_time_t expires;
    int additional_sec;
    char *timestr;

    switch (code[0]) {
    case 'M':
        if (r->finfo.filetype == APR_NOFILE) {
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
    if (expires < r->request_time) {
        expires = r->request_time;
    }
    apr_table_mergen(t, "Cache-Control",
                     apr_psprintf(r->pool, "max-age=%" APR_TIME_T_FMT,
                                  apr_time_sec(expires - r->request_time)));
    timestr = apr_palloc(r->pool, APR_RFC822_DATE_LEN);
    apr_rfc822_date(timestr, expires);
    apr_table_setn(t, "Expires", timestr);
    return OK;
}