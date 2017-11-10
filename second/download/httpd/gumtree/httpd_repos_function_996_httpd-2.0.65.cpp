static void splitout_queryargs(request_rec *r, int qsappend)
{
    char *q;
    char *olduri;

    /* don't touch, unless it's an http or mailto URL.
     * See RFC 1738 and RFC 2368.
     */
    if (   is_absolute_uri(r->filename)
        && strncasecmp(r->filename, "http", 4)
        && strncasecmp(r->filename, "mailto", 6)) {
        r->args = NULL; /* forget the query that's still flying around */
        return;
    }

    q = strchr(r->filename, '?');
    if (q != NULL) {
        olduri = apr_pstrdup(r->pool, r->filename);
        *q++ = '\0';
        if (qsappend) {
            r->args = apr_pstrcat(r->pool, q, "&", r->args, NULL);
        }
        else {
            r->args = apr_pstrdup(r->pool, q);
        }
        if (strlen(r->args) == 0) {
            r->args = NULL;
            rewritelog(r, 3, "split uri=%s -> uri=%s, args=<none>", olduri,
                       r->filename);
        }
        else {
            if (r->args[strlen(r->args)-1] == '&') {
                r->args[strlen(r->args)-1] = '\0';
            }
            rewritelog(r, 3, "split uri=%s -> uri=%s, args=%s", olduri,
                       r->filename, r->args);
        }
    }

    return;
}