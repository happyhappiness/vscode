static void do_debug_log(request_rec *r, const char *hookname)
{
    log_debug_dirconf *dconf = ap_get_module_config(r->per_dir_config, &log_debug_module);
    int i;
    if (dconf->entries == NULL)
        return;

    for (i = 0; i < dconf->entries->nelts; i++) {
        const char *msg, *err;
        msg_entry *entry = APR_ARRAY_IDX(dconf->entries, i, msg_entry *);
        if (entry->hook != allhooks && entry->hook != hookname)
            continue;
        if (entry->condition) {
            int ret = ap_expr_exec(r, entry->condition, &err);
            if (err) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00640)
                              "Can't evaluate condition: %s", err);
                continue;
            }
            if (!ret)
                continue;
        }
        msg = ap_expr_str_exec(r, entry->msg_expr, &err);
        if (err)
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00641)
                          "Can't evaluate message expression: %s", err);
        if (APLOGrdebug(r))
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, "%s (%s hook, %s:%d)",
                           msg, hookname, entry->msg_expr->filename,
                           entry->msg_expr->line_number);
        else
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, "%s", msg);
    }
}