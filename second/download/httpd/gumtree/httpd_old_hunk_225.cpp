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

static void register_hooks(apr_pool_t *p)
{
    ap_hook_fixups(add_expires,NULL,NULL,APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA expires_module =
{
    STANDARD20_MODULE_STUFF,
    create_dir_expires_config,  /* dir config creater */
