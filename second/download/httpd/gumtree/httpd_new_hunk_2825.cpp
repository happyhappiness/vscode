        else {
            if (apr_table_get(r->subprocess_env, &envar[1]) != NULL) {
                return DECLINED;
            }
        }
    }
    else if (cls->condition_expr != NULL) {
        const char *err;
        int rc = ap_expr_exec(r, cls->condition_expr, &err);
        if (rc < 0)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(00644)
                           "Error evaluating log condition: %s", err);
        if (rc <= 0)
            return DECLINED;
    }

    format = cls->format ? cls->format : default_format;

    strs = apr_palloc(r->pool, sizeof(char *) * (format->nelts));
    strl = apr_palloc(r->pool, sizeof(int) * (format->nelts));
    items = (log_format_item *) format->elts;
