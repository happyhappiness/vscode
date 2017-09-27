ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r,
                      "authorization result of %s: %s "
                      "(directive limited to other methods)",
                      format_authz_command(r->pool, section),
                      format_authz_result(auth_result));