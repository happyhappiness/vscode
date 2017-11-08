int ap_cache_control(request_rec *r, cache_control_t *cc,
        const char *cc_header, const char *pragma_header, apr_table_t *headers)
{
    char *last;

    if (cc->parsed) {
        return cc->cache_control || cc->pragma;
    }

    cc->parsed = 1;
    cc->max_age_value = -1;
    cc->max_stale_value = -1;
    cc->min_fresh_value = -1;
    cc->s_maxage_value = -1;

    if (pragma_header) {
        char *header = apr_pstrdup(r->pool, pragma_header);
        const char *token = cache_strqtok(header, CACHE_SEPARATOR, &last);
        while (token) {
            /* handle most common quickest case... */
            if (!strcmp(token, "no-cache")) {
                cc->no_cache = 1;
            }
            /* ...then try slowest case */
            else if (!strcasecmp(token, "no-cache")) {
                cc->no_cache = 1;
            }
            token = cache_strqtok(NULL, CACHE_SEPARATOR, &last);
        }
        cc->pragma = 1;
    }

    if (cc_header) {
        char *header = apr_pstrdup(r->pool, cc_header);
        const char *token = cache_strqtok(header, CACHE_SEPARATOR, &last);
        while (token) {
            switch (token[0]) {
            case 'n':
            case 'N': {
                /* handle most common quickest cases... */
                if (!strcmp(token, "no-cache")) {
                    cc->no_cache = 1;
                }
                else if (!strcmp(token, "no-store")) {
                    cc->no_store = 1;
                }
                /* ...then try slowest cases */
                else if (!strncasecmp(token, "no-cache", 8)) {
                    if (token[8] == '=') {
                        if (apr_table_get(headers, token + 9)) {
                            cc->no_cache_header = 1;
                        }
                    }
                    else if (!token[8]) {
                        cc->no_cache = 1;
                    }
                    break;
                }
                else if (!strcasecmp(token, "no-store")) {
                    cc->no_store = 1;
                }
                else if (!strcasecmp(token, "no-transform")) {
                    cc->no_transform = 1;
                }
                break;
            }
            case 'm':
            case 'M': {
                /* handle most common quickest cases... */
                if (!strcmp(token, "max-age=0")) {
                    cc->max_age = 1;
                    cc->max_age_value = 0;
                }
                else if (!strcmp(token, "must-revalidate")) {
                    cc->must_revalidate = 1;
                }
                /* ...then try slowest cases */
                else if (!strncasecmp(token, "max-age", 7)) {
                    if (token[7] == '=') {
                        cc->max_age = 1;
                        cc->max_age_value = apr_atoi64(token + 8);
                    }
                    break;
                }
                else if (!strncasecmp(token, "max-stale", 9)) {
                    if (token[9] == '=') {
                        cc->max_stale = 1;
                        cc->max_stale_value = apr_atoi64(token + 10);
                    }
                    else if (!token[10]) {
                        cc->max_stale = 1;
                        cc->max_stale_value = -1;
                    }
                    break;
                }
                else if (!strncasecmp(token, "min-fresh", 9)) {
                    if (token[9] == '=') {
                        cc->min_fresh = 1;
                        cc->min_fresh_value = apr_atoi64(token + 10);
                    }
                    break;
                }
                else if (!strcasecmp(token, "must-revalidate")) {
                    cc->must_revalidate = 1;
                }
                break;
            }
            case 'o':
            case 'O': {
                if (!strcasecmp(token, "only-if-cached")) {
                    cc->only_if_cached = 1;
                }
                break;
            }
            case 'p':
            case 'P': {
                /* handle most common quickest cases... */
                if (!strcmp(token, "private")) {
                    cc->private = 1;
                }
                /* ...then try slowest cases */
                else if (!strcasecmp(token, "public")) {
                    cc->public = 1;
                }
                else if (!strncasecmp(token, "private", 7)) {
                    if (token[7] == '=') {
                        if (apr_table_get(headers, token + 8)) {
                            cc->private_header = 1;
                        }
                    }
                    else if (!token[7]) {
                        cc->private = 1;
                    }
                    break;
                }
                else if (!strcasecmp(token, "proxy-revalidate")) {
                    cc->proxy_revalidate = 1;
                }
                break;
            }
            case 's':
            case 'S': {
                if (!strncasecmp(token, "s-maxage", 8)) {
                    if (token[8] == '=') {
                        cc->s_maxage = 1;
                        cc->s_maxage_value = apr_atoi64(token + 9);
                    }
                    break;
                }
                break;
            }
            }
            token = cache_strqtok(NULL, CACHE_SEPARATOR, &last);
        }
        cc->cache_control = 1;
    }

    return (cc_header != NULL || pragma_header != NULL);
}