static int cache_control_remove(request_rec *r, const char *cc_header,
        apr_table_t *headers)
{
    char *last, *slast;
    int found = 0;

    if (cc_header) {
        char *header = apr_pstrdup(r->pool, cc_header);
        char *token = cache_strqtok(header, CACHE_SEPARATOR, &last);
        while (token) {
            switch (token[0]) {
            case 'n':
            case 'N': {
                if (!ap_cstr_casecmpn(token, "no-cache", 8)) {
                    if (token[8] == '=') {
                        const char *header = cache_strqtok(token + 9,
                                CACHE_SEPARATOR "\"", &slast);
                        while (header) {
                            apr_table_unset(headers, header);
                            header = cache_strqtok(NULL, CACHE_SEPARATOR "\"",
                                    &slast);
                        }
                        found = 1;
                    }
                    break;
                }
                break;
            }
            case 'p':
            case 'P': {
                if (!ap_cstr_casecmpn(token, "private", 7)) {
                    if (token[7] == '=') {
                        const char *header = cache_strqtok(token + 8,
                                CACHE_SEPARATOR "\"", &slast);
                        while (header) {
                            apr_table_unset(headers, header);
                            header = cache_strqtok(NULL, CACHE_SEPARATOR "\"",
                                    &slast);
                        }
                        found = 1;
                    }
                }
                break;
            }
            }
            token = cache_strqtok(NULL, CACHE_SEPARATOR, &last);
        }
    }

    return found;
}