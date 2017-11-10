static void splitout_queryargs(request_rec *r, int qsappend)
{
    char *q;

    /* don't touch, unless it's an http or mailto URL.
     * See RFC 1738 and RFC 2368.
     */
    if (is_absolute_uri(r->filename)
        && strncasecmp(r->filename, "ajp", 3)
        && strncasecmp(r->filename, "balancer", 8)
        && strncasecmp(r->filename, "http", 4)
        && strncasecmp(r->filename, "mailto", 6)) {
        r->args = NULL; /* forget the query that's still flying around */
        return;
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