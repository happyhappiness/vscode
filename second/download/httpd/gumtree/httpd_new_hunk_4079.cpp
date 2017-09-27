        }
        msg = ap_expr_str_exec(r, entry->msg_expr, &err);
        if (err)
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00641)
                          "Can't evaluate message expression: %s", err);
        if (APLOGrdebug(r))
            /* Intentional no APLOGNO */
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                           "%s (%s hook, %s:%d)",
                           msg, hookname, entry->msg_expr->filename,
                           entry->msg_expr->line_number);
        else
            /* Intentional no APLOGNO */
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                          "%s", msg);
    }
}

static int log_debug_log_transaction(request_rec *r)
{
    do_debug_log(r, hooks[0]);
