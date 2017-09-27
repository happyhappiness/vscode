        rv = authz_dbd_group_query(r, cfg, groups);
        if (rv != OK) {
            return AUTHZ_GENERAL_ERROR;
        }
    }

    t = require_args;
    while (t[0]) {
        w = ap_getword_white(r->pool, &t);
        for (i=0; i < groups->nelts; ++i) {
            if (!strcmp(w, ((const char**)groups->elts)[i])) {
                return AUTHZ_GRANTED;
            }
