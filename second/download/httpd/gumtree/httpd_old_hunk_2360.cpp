    }
    else {
        switch (ap_satisfies(r)) {
        case SATISFY_ALL:
        case SATISFY_NOSPEC:
            if ((access_status = ap_run_access_checker(r)) != OK) {
                return decl_die(access_status, "check access", r);
            }

            if ((access_status = ap_run_check_user_id(r)) != OK) {
                return decl_die(access_status, "check user", r);
            }

            if ((access_status = ap_run_auth_checker(r)) != OK) {
                return decl_die(access_status, "check authorization", r);
            }
            break;
        case SATISFY_ANY:
            if ((access_status = ap_run_access_checker(r)) != OK) {

                if ((access_status = ap_run_check_user_id(r)) != OK) {
                    return decl_die(access_status, "check user", r);
                }

                if ((access_status = ap_run_auth_checker(r)) != OK) {
                    return decl_die(access_status, "check authorization", r);
                }
            }
            break;
        }
