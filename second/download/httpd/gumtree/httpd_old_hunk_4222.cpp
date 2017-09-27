    char *w;

    /* the require line is an expression, which is evaluated now. */
    require = ap_expr_str_exec(r, expr, &err);
    if (err) {
      ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(03354)
                    "Can't evaluate require expression: %s", err);
      return AUTHZ_DENIED;
    }

    /* tokenize expected list of names */
    t = require;
