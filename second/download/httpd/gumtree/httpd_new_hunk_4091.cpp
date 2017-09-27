     * doubled slashes)
     */

    return urip - uri;
}

static char *try_alias(request_rec *r)
{
    alias_dir_conf *dirconf =
            (alias_dir_conf *) ap_get_module_config(r->per_dir_config, &alias_module);

    if (dirconf->alias) {
        const char *err = NULL;

        char *found = apr_pstrdup(r->pool,
                ap_expr_str_exec(r, dirconf->alias, &err));
        if (err) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02825)
                          "Can't evaluate alias expression: %s", err);
            return PREGSUB_ERROR;
        }

        if (dirconf->handler) { /* Set handler, and leave a note for mod_cgi */
            r->handler = dirconf->handler;
            apr_table_setn(r->notes, "alias-forced-type", r->handler);
        }
        /* XXX This is as SLOW as can be, next step, we optimize
         * and merge to whatever part of the found path was already
         * canonicalized.  After I finish eliminating os canonical.
         * Better fail test for ap_server_root_relative needed here.
         */
        found = ap_server_root_relative(r->pool, found);
        return found;

    }

    return NULL;
}

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

static char *try_alias_list(request_rec *r, apr_array_header_t *aliases,
                            int is_redir, int *status)
{
    alias_entry *entries = (alias_entry *) aliases->elts;
    ap_regmatch_t regm[AP_MAX_REG_MATCH];
