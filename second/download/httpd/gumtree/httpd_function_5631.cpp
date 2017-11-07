static char *try_redirect(request_rec *r, int *status)
{
    alias_dir_conf *dirconf =
            (alias_dir_conf *) ap_get_module_config(r->per_dir_config, &alias_module);

    if (dirconf->redirect_set) {
        apr_uri_t uri;
        const char *err = NULL;
        char *found = "";

        if (dirconf->redirect) {

            found = apr_pstrdup(r->pool,
                    ap_expr_str_exec(r, dirconf->redirect, &err));
            if (err) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02826)
                              "Can't evaluate redirect expression: %s", err);
                return PREGSUB_ERROR;
            }

            apr_uri_parse(r->pool, found, &uri);
            /* Do not escape the query string or fragment. */
            found = apr_uri_unparse(r->pool, &uri, APR_URI_UNP_OMITQUERY);
            found = ap_escape_uri(r->pool, found);
            if (uri.query) {
                found = apr_pstrcat(r->pool, found, "?", uri.query, NULL);
            }
            if (uri.fragment) {
                found = apr_pstrcat(r->pool, found, "#", uri.fragment, NULL);
            }

        }

        *status = dirconf->redirect_status;
        return found;

    }

    return NULL;
}