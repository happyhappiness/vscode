            /* We weren't called in the authentication phase, so we didn't have a
             * chance to set the user field. Do so now. */
            req->user = r->user;
        }
    }

    require = ap_expr_str_exec(r, expr, &err);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02586)
                      "auth_ldap authorize: require group: Can't evaluate expression: %s",
                      err);
        return AUTHZ_DENIED;
    }

    t = require;

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01713)
                  "auth_ldap authorize: require group: testing for group "
                  "membership in \"%s\"",
                  t);

