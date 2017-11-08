static int spot_cookie(request_rec *r)
{
    cookie_dir_rec *dcfg = ap_get_module_config(r->per_dir_config,
						&usertrack_module);
    const char *cookie;
    const char *value;

    if (!dcfg->enabled) {
        return DECLINED;
    }

    if ((cookie = apr_table_get(r->headers_in,
                                (dcfg->style == CT_COOKIE2
                                 ? "Cookie2"
                                 : "Cookie"))))
        if ((value = ap_strstr_c(cookie, dcfg->cookie_name))) {
            char *cookiebuf, *cookieend;

            value += strlen(dcfg->cookie_name) + 1;  /* Skip over the '=' */
            cookiebuf = apr_pstrdup(r->pool, value);
            cookieend = strchr(cookiebuf, ';');
            if (cookieend)
                *cookieend = '\0';      /* Ignore anything after a ; */

            /* Set the cookie in a note, for logging */
            apr_table_setn(r->notes, "cookie", cookiebuf);

            return DECLINED;    /* There's already a cookie, no new one */
        }
    make_cookie(r);
    return OK;                  /* We set our cookie */
}