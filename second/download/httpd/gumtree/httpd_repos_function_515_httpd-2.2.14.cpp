static int scan_meta_file(request_rec *r, apr_file_t *f)
{
    char w[MAX_STRING_LEN];
    char *l;
    int p;
    apr_table_t *tmp_headers;

    tmp_headers = apr_table_make(r->pool, 5);
    while (apr_file_gets(w, MAX_STRING_LEN - 1, f) == APR_SUCCESS) {

    /* Delete terminal (CR?)LF */
        p = strlen(w);
        if (p > 0 && w[p - 1] == '\n') {
            if (p > 1 && w[p - 2] == '\015')
                w[p - 2] = '\0';
            else
                w[p - 1] = '\0';
        }

        if (w[0] == '\0') {
            return OK;
        }

        /* if we see a bogus header don't ignore it. Shout and scream */

        if (!(l = strchr(w, ':'))) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                "malformed header in meta file: %s", r->filename);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        *l++ = '\0';
        while (*l && apr_isspace(*l))
            ++l;

        if (!strcasecmp(w, "Content-type")) {
            char *tmp;
            /* Nuke trailing whitespace */

            char *endp = l + strlen(l) - 1;
            while (endp > l && apr_isspace(*endp))
            *endp-- = '\0';

            tmp = apr_pstrdup(r->pool, l);
            ap_content_type_tolower(tmp);
            ap_set_content_type(r, tmp);
        }
        else if (!strcasecmp(w, "Status")) {
            sscanf(l, "%d", &r->status);
            r->status_line = apr_pstrdup(r->pool, l);
        }
        else {
            apr_table_set(tmp_headers, w, l);
        }
    }
    apr_table_overlap(r->headers_out, tmp_headers, APR_OVERLAP_TABLES_SET);
    return OK;
}