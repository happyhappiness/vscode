static int check_gzip(request_rec *r, apr_table_t *hdrs1, apr_table_t *hdrs2)
{
    int found = 0;
    apr_table_t *hdrs = hdrs1;
    const char *encoding = apr_table_get(hdrs, "Content-Encoding");

    if (!encoding && (hdrs2 != NULL)) {
        /* the output filter has two tables and a content_encoding to check */
        encoding = apr_table_get(hdrs2, "Content-Encoding");
        hdrs = hdrs2;
        if (!encoding) {
            encoding = r->content_encoding;
            hdrs = NULL;
        }
    }
    if (encoding && *encoding) {

        /* check the usual/simple case first */
        if (!strcasecmp(encoding, "gzip")
            || !strcasecmp(encoding, "x-gzip")) {
            found = 1;
            if (hdrs) {
                apr_table_unset(hdrs, "Content-Encoding");
            }
            else {
                r->content_encoding = NULL;
            }
        }
        else if (ap_strchr_c(encoding, ',') != NULL) {
            /* If the outermost encoding isn't gzip, there's nothing
             * we can do.  So only check the last non-identity token
             */
            char *new_encoding = apr_pstrdup(r->pool, encoding);
            char *ptr;
            for(;;) {
                char *token = ap_strrchr(new_encoding, ',');
                if (!token) {        /* gzip:identity or other:identity */
                    if (!strcasecmp(new_encoding, "gzip")
                        || !strcasecmp(new_encoding, "x-gzip")) {
                        found = 1;
                        if (hdrs) {
                            apr_table_unset(hdrs, "Content-Encoding");
                        }
                        else {
                            r->content_encoding = NULL;
                        }
                    }
                    break; /* seen all tokens */
                }
                for (ptr=token+1; apr_isspace(*ptr); ++ptr);
                if (!strcasecmp(ptr, "gzip")
                    || !strcasecmp(ptr, "x-gzip")) {
                    *token = '\0';
                    if (hdrs) {
                        apr_table_setn(hdrs, "Content-Encoding", new_encoding);
                    }
                    else {
                        r->content_encoding = new_encoding;
                    }
                    found = 1;
                }
                else if (!ptr[0] || !strcasecmp(ptr, "identity")) {
                    *token = '\0';
                    continue; /* strip the token and find the next one */
                }
                break; /* found a non-identity token */
            }
        }
    }
    /*
     * If we have dealt with the headers above but content_encoding was set
     * before sync it with the new value in the hdrs table as
     * r->content_encoding takes precedence later on in the http_header_filter
     * and hence would destroy what we have just set in the hdrs table.
     */
    if (hdrs && r->content_encoding) {
        r->content_encoding = apr_table_get(hdrs, "Content-Encoding");
    }
    return found;
}