            /* We weren't called in the authentication phase, so we didn't have a
             * chance to set the user field. Do so now. */
            req->user = r->user;
        }
    }

    t = require_args;

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01713)
                  "auth_ldap authorize: require group: testing for group "
                  "membership in \"%s\"",
                  t);

