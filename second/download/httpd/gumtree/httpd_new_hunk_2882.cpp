        /* ignore late headers in early calls */
        else if (early && (envar != condition_early)) {
            continue;
        }
        /* Do we have an expression to evaluate? */
        else if (hdr->expr != NULL) {
            const char *err = NULL;
            int eval = ap_expr_exec(r, hdr->expr, &err);
            if (err) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01501)
                              "Failed to evaluate expression (%s) - ignoring",
                              err);
            }
            else if (!eval) {
                continue;
            }
        }
        /* Have any conditional envar-controlled Header processing to do? */
