ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "[%" APR_PID_T_FMT "]"
                          " util_ldap: user %s not found in subgroup (%s) at"
                          " level %d of %d.", getpid(), r->user, group,
                          cur_subgroup_depth+1, max_subgroup_depth);