            continue;
        }
        /* ignore late headers in early calls */
        else if (early && (envar != condition_early)) {
            continue;
        }
        /* Do we have an expression to evaluate? */
        else if (hdr->expr != NULL) {
            int err = 0;
            int eval = ap_expr_eval(r, hdr->expr, &err, NULL,
                                    ap_expr_string, NULL);
            if (err) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Failed to evaluate expression - ignoring");
            }
            else if (!eval) {
                continue;
            }
        }
        /* Have any conditional envar-controlled Header processing to do? */
        else if (envar && !early) {
            if (*envar != '!') {
                if (apr_table_get(r->subprocess_env, envar) == NULL)
                    continue;
            }
