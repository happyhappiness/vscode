static char *imap_url(request_rec *r, const char *base, const char *value)
{
/* translates a value into a URL. */
    int slen, clen;
    char *string_pos = NULL;
    const char *string_pos_const = NULL;
    char *directory = NULL;
    const char *referer = NULL;
    char *my_base;

    if (!strcasecmp(value, "map") || !strcasecmp(value, "menu")) {
        return ap_construct_url(r->pool, r->uri, r);
    }

    if (!strcasecmp(value, "nocontent") || !strcasecmp(value, "error")) {
        return apr_pstrdup(r->pool, value);      /* these are handled elsewhere,
                                                so just copy them */
    }

    if (!strcasecmp(value, "referer")) {
        referer = apr_table_get(r->headers_in, "Referer");
        if (referer && *referer) {
            return ap_escape_html(r->pool, referer);
        }
        else {
            /* XXX:  This used to do *value = '\0'; ... which is totally bogus
             * because it hammers the passed in value, which can be a string
             * constant, or part of a config, or whatever.  Total garbage.
             * This works around that without changing the rest of this
             * code much
             */
            value = "";      /* if 'referer' but no referring page,
                                null the value */
        }
    }

    string_pos_const = value;
    while (apr_isalpha(*string_pos_const)) {
        string_pos_const++;           /* go along the URL from the map
                                         until a non-letter */
    }
    if (*string_pos_const == ':') {
        /* if letters and then a colon (like http:) */
        /* it's an absolute URL, so use it! */
        return apr_pstrdup(r->pool, value);
    }

    if (!base || !*base) {
        if (value && *value) {
            return apr_pstrdup(r->pool, value); /* no base: use what is given */
        }
        /* no base, no value: pick a simple default */
        return ap_construct_url(r->pool, "/", r);
    }

    /* must be a relative URL to be combined with base */
    if (ap_strchr_c(base, '/') == NULL && (!strncmp(value, "../", 3)
        || !strcmp(value, ".."))) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    "invalid base directive in map file: %s", r->uri);
        return NULL;
    }
    my_base = apr_pstrdup(r->pool, base);
    string_pos = my_base;
    while (*string_pos) {
        if (*string_pos == '/' && *(string_pos + 1) == '/') {
            string_pos += 2;    /* if there are two slashes, jump over them */
            continue;
        }
        if (*string_pos == '/') {       /* the first single slash */
            if (value[0] == '/') {
                *string_pos = '\0';
            }                   /* if the URL from the map starts from root,
                                   end the base URL string at the first single
                                   slash */
            else {
                directory = string_pos;         /* save the start of
                                                   the directory portion */

                string_pos = strrchr(string_pos, '/');  /* now reuse
                                                           string_pos */
                string_pos++;   /* step over that last slash */
                *string_pos = '\0';
            }                   /* but if the map url is relative, leave the
                                   slash on the base (if there is one) */
            break;
        }
        string_pos++;           /* until we get to the end of my_base without
                                   finding a slash by itself */
    }

    while (!strncmp(value, "../", 3) || !strcmp(value, "..")) {

        if (directory && (slen = strlen(directory))) {

            /* for each '..',  knock a directory off the end
               by ending the string right at the last slash.
               But only consider the directory portion: don't eat
               into the server name.  And only try if a directory
               portion was found */

            clen = slen - 1;

            while ((slen - clen) == 1) {

                if ((string_pos = strrchr(directory, '/'))) {
                    *string_pos = '\0';
                }
                clen = strlen(directory);
                if (clen == 0) {
                    break;
                }
            }

            value += 2;         /* jump over the '..' that we found in the
                                   value */
        }
        else if (directory) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "invalid directory name in map file: %s", r->uri);
            return NULL;
        }

        if (!strncmp(value, "/../", 4) || !strcmp(value, "/..")) {
            value++;            /* step over the '/' if there are more '..'
                                   to do.  This way, we leave the starting
                                   '/' on value after the last '..', but get
                                   rid of it otherwise */
        }

    }                           /* by this point, value does not start
                                   with '..' */

    if (value && *value) {
        return apr_pstrcat(r->pool, my_base, value, NULL);
    }
    return my_base;
}