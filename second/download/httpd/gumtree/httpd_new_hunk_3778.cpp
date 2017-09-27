                    return decl_die(access_status, "check user", r);
                }
                if ((access_status = ap_run_auth_checker(r)) != OK) {
                    return decl_die(access_status, "check authorization", r);
                }
            }
            else if (access_status == OK) {
                ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r,
                              "request authorized without authentication by "
                              "access_checker_ex hook: %s", r->uri);
            }
            else {
                return decl_die(access_status, "check access", r);
            }
            break;
        case SATISFY_ANY:
            if ((access_status = ap_run_access_checker(r)) == OK) {
                ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r,
                              "request authorized without authentication by "
                              "access_checker hook and 'Satisfy any': %s",
                              r->uri);
                break;
            }

            access_status = ap_run_access_checker_ex(r);
            if (access_status == DECLINED
                || (access_status == OK && ap_run_force_authn(r) == OK)) {
                if ((access_status = ap_run_check_user_id(r)) != OK) {
                    return decl_die(access_status, "check user", r);
                }
                if (r->user == NULL) {
                    /* don't let buggy authn module crash us in authz */
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00028)
