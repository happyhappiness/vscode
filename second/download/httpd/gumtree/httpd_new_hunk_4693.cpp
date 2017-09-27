    }
    else if (r->main && (r->main->per_dir_config == r->per_dir_config)) {
        r->user = r->main->user;
        r->ap_auth_type = r->main->ap_auth_type;
    }
    else {
        /* A module using a confusing API (ap_get_basic_auth_pw) caused
        ** r->user to be filled out prior to check_authn hook. We treat
        ** it is inadvertent.
        */
        if (r->user && apr_table_get(r->notes, AP_GET_BASIC_AUTH_PW_NOTE)) { 
            r->user = NULL;
        }

        switch (ap_satisfies(r)) {
        case SATISFY_ALL:
        case SATISFY_NOSPEC:
            if ((access_status = ap_run_access_checker(r)) != OK) {
                return decl_die(access_status,
                                "check access (with Satisfy All)", r);
