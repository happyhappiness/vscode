                                   r);
                }
            }
            break;

        case SATISFY_ANY:
            if (((access_status = ap_run_access_checker(r)) != 0)) {
                if (!ap_some_auth_required(r)) {
                    return decl_die(access_status, "check access", r);
                }

                if (((access_status = ap_run_check_user_id(r)) != 0)
                    || !ap_auth_type(r)) {
                    return decl_die(access_status, ap_auth_type(r)
                                  ? "check user.  No user file?"
