static const char *cmd_parseflagfield(apr_pool_t *p, void *cfg, char *key,
                                      const char *(*parse)(apr_pool_t *,
                                                           void *,
                                                           char *, char *))
{
    char *val, *nextp, *endp;
    const char *err;

    endp = key + strlen(key) - 1;
    if (*key != '[' || *endp != ']') {
        return "RewriteCond: bad flag delimiters";
    }

    *endp = ','; /* for simpler parsing */
    ++key;

    while (*key) {
        /* skip leading spaces */
        while (apr_isspace(*key)) {
            ++key;
        }

        if (!*key || (nextp = ap_strchr(key, ',')) == NULL) { /* NULL should not
                                                               * happen, but ...
                                                               */
            break;
        }

        /* strip trailing spaces */
        endp = nextp - 1;
        while (apr_isspace(*endp)) {
            --endp;
        }
        *++endp = '\0';

        /* split key and val */
        val = ap_strchr(key, '=');
        if (val) {
            *val++ = '\0';
        }
        else {
            val = endp;
        }

        err = parse(p, cfg, key, val);
        if (err) {
            return err;
        }

        key = nextp + 1;
    }

    return NULL;
}