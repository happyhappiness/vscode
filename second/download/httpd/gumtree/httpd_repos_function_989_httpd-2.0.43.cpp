static void splitout_queryargs(request_rec *r, int qsappend)
{
    char *q;
    char *olduri;

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