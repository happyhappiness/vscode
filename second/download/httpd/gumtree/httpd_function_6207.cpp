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