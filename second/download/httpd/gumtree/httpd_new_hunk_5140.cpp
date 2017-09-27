            return AUTHZ_DENIED;
        }

        orig_groups = groups;
    }

    require = ap_expr_str_exec(r, expr, &err);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02591)
                      "authz_dbm authorize: require dbm-group: Can't "
                      "evaluate require expression: %s", err);
        return AUTHZ_DENIED;
    }

    t = require;
    while ((w = ap_getword_white(r->pool, &t)) && w[0]) {
        groups = orig_groups;
        while (groups[0]) {
            v = ap_getword(r->pool, &groups, ',');
            if (!strcmp(v, w)) {
                return AUTHZ_GRANTED;
