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
            if (!ap_cstr_casecmp(token, "no-cache")) {
                cc->no_cache = 1;
            }
            token = cache_strqtok(NULL, CACHE_SEPARATOR, &last);
        }
        cc->pragma = 1;
    }

    if (cc_header) {
        char *endp;
        apr_off_t offt;
        char *header = apr_pstrdup(r->pool, cc_header);
        const char *token = cache_strqtok(header, CACHE_SEPARATOR, &last);
        while (token) {
            switch (token[0]) {
            case 'n':
            case 'N': {
                if (!ap_cstr_casecmpn(token, "no-cache", 8)) {
                    if (token[8] == '=') {
                        cc->no_cache_header = 1;
                    }
                    else if (!token[8]) {
                        cc->no_cache = 1;
                    }
                }
                else if (!ap_cstr_casecmp(token, "no-store")) {
                    cc->no_store = 1;
                }
                else if (!ap_cstr_casecmp(token, "no-transform")) {
                    cc->no_transform = 1;
                }
                break;
            }
            case 'm':
            case 'M': {
                if (!ap_cstr_casecmpn(token, "max-age", 7)) {
                    if (token[7] == '='
                            && !apr_strtoff(&offt, token + 8, &endp, 10)
                            && endp > token + 8 && !*endp) {
                        cc->max_age = 1;
                        cc->max_age_value = offt;
                    }
                }
                else if (!ap_cstr_casecmp(token, "must-revalidate")) {
                    cc->must_revalidate = 1;
                }
                else if (!ap_cstr_casecmpn(token, "max-stale", 9)) {
                    if (token[9] == '='
                            && !apr_strtoff(&offt, token + 10, &endp, 10)
                            && endp > token + 10 && !*endp) {
                        cc->max_stale = 1;
                        cc->max_stale_value = offt;
                    }
                    else if (!token[9]) {
                        cc->max_stale = 1;
                        cc->max_stale_value = -1;
                    }
                }
                else if (!ap_cstr_casecmpn(token, "min-fresh", 9)) {
                    if (token[9] == '='
                            && !apr_strtoff(&offt, token + 10, &endp, 10)
                            && endp > token + 10 && !*endp) {
                        cc->min_fresh = 1;
                        cc->min_fresh_value = offt;
                    }
                }
                break;
            }
            case 'o':
            case 'O': {
                if (!ap_cstr_casecmp(token, "only-if-cached")) {
                    cc->only_if_cached = 1;
                }
                break;
            }
            case 'p':
            case 'P': {
                if (!ap_cstr_casecmp(token, "public")) {
                    cc->public = 1;
                }
                else if (!ap_cstr_casecmpn(token, "private", 7)) {
                    if (token[7] == '=') {
                        cc->private_header = 1;
                    }
                    else if (!token[7]) {
                        cc->private = 1;
                    }
                }
                else if (!ap_cstr_casecmp(token, "proxy-revalidate")) {
                    cc->proxy_revalidate = 1;
                }
                break;
            }
            case 's':
            case 'S': {
                if (!ap_cstr_casecmpn(token, "s-maxage", 8)) {
                    if (token[8] == '='
                            && !apr_strtoff(&offt, token + 9, &endp, 10)
                            && endp > token + 9 && !*endp) {
                        cc->s_maxage = 1;
                        cc->s_maxage_value = offt;
                    }
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