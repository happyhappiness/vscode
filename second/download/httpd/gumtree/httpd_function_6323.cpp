static void fix_cgivars(request_rec *r, fcgi_dirconf_t *dconf)
{
    sei_entry *entries;
    const char *err, *src;
    int i = 0, rc = 0;
    ap_regmatch_t regm[AP_MAX_REG_MATCH];

    entries = (sei_entry *) dconf->env_fixups->elts;
    for (i = 0; i < dconf->env_fixups->nelts; i++) {
        sei_entry *entry = &entries[i];

        if (entry->envname[0] == '!') {
            apr_table_unset(r->subprocess_env, entry->envname+1);
        }
        else if (0 < (rc = ap_expr_exec_re(r, entry->cond, AP_MAX_REG_MATCH, regm, &src, &err)))  {
            const char *val = ap_expr_str_exec_re(r, entry->subst, AP_MAX_REG_MATCH, regm, &src, &err);
            if (err) {
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(03514)
                              "Error evaluating expression for replacement of %s: '%s'",
                               entry->envname, err);
                continue;
            }
            if (APLOGrtrace4(r)) {
                const char *oldval = apr_table_get(r->subprocess_env, entry->envname);
                ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
                              "fix_cgivars: override %s from '%s' to '%s'",
                              entry->envname, oldval, val);

            }
            apr_table_setn(r->subprocess_env, entry->envname, val);
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE8, 0, r, "fix_cgivars: Condition returned %d", rc);
        }
    }
}