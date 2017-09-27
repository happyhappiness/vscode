r(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r,
                  "AuthType %s configured without corresponding module",
                  ap_auth_type(r));