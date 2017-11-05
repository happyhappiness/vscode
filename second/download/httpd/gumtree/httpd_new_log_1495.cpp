ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "[%" APR_PID_T_FMT "] auth_ldap authorize: require group: "
                      "testing for %s: %s (%s)", getpid(),
                      ent[i].name, sec->group_attrib_is_dn ? req->dn : req->user, t);