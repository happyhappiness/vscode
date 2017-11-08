static void splitout_queryargs(request_rec *r, int qsappend, int qsdiscard)
{
    char *q;
    int split;

    /* don't touch, unless it's a scheme for which a query string makes sense.
     * See RFC 1738 and RFC 2368.
     */
    if (is_absolute_uri(r->filename, &split)
        && !split) {
        r->args = NULL; /* forget the query that's still flying around */
        return;
    }

    if ( qsdiscard ) {
        r->args = NULL; /* Discard query string */
        rewritelog((r, 2, NULL, "discarding query string"));
    }

    q = ap_strchr(r->filename, '?');
    if (q != NULL) {
        char *olduri;
        apr_size_t len;

        olduri = apr_pstrdup(r->pool, r->filename);
        *q++ = '\0';
        if (qsappend) {
            r->args = apr_pstrcat(r->pool, q, "&", r->args, NULL);
        }
        else {
            r->args = apr_pstrdup(r->pool, q);
        }

        len = strlen(r->args);
        if (!len) {
            r->args = NULL;
        }
        else if (r->args[len-1] == '&') {
            r->args[len-1] = '\0';
        }

        rewritelog((r, 3, NULL, "split uri=%s -> uri=%s, args=%s", olduri,
                    r->filename, r->args ? r->args : "<none>"));
    }

    return;
}