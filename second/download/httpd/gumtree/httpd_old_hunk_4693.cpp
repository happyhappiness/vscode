    }
    else if (r->main && (r->main->per_dir_config == r->per_dir_config)) {
        r->user = r->main->user;
        r->ap_auth_type = r->main->ap_auth_type;
    }
    else {
        switch (ap_satisfies(r)) {
        case SATISFY_ALL:
        case SATISFY_NOSPEC:
            if ((access_status = ap_run_access_checker(r)) != OK) {
                return decl_die(access_status,
                                "check access (with Satisfy All)", r);
