    }
    else if (r->prev && (r->prev->per_dir_config == r->per_dir_config)) {
        r->user = r->prev->user;
        r->ap_auth_type = r->prev->ap_auth_type;
    }
    else {
        switch (ap_satisfies(r)) {
        case SATISFY_ALL:
        case SATISFY_NOSPEC:
            if ((access_status = ap_run_access_checker(r)) != 0) {
                return decl_die(access_status, "check access", r);
            }
