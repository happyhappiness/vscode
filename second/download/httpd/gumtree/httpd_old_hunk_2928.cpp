        return DECLINED;
    }

    if ((cookie_header = apr_table_get(r->headers_in, "Cookie"))) {
        if (!ap_regexec(dcfg->regexp, cookie_header, NUM_SUBS, regm, 0)) {
            char *cookieval = NULL;
            /* Our regexp,
             * ^cookie_name=([^;]+)|;[ \t]+cookie_name=([^;]+)
             * only allows for $1 or $2 to be available. ($0 is always
             * filled with the entire matched expression, not just
             * the part in parentheses.) So just check for either one
             * and assign to cookieval if present. */
            if (regm[1].rm_so != -1) {
                cookieval = ap_pregsub(r->pool, "$1", cookie_header,
                                       NUM_SUBS, regm);
            }
            if (regm[2].rm_so != -1) {
                cookieval = ap_pregsub(r->pool, "$2", cookie_header,
                                       NUM_SUBS, regm);
            }
            /* Set the cookie in a note, for logging */
            apr_table_setn(r->notes, "cookie", cookieval);

            return DECLINED;    /* There's already a cookie, no new one */
        }
