            /* if we aren't authoritative, any require directive could be
             * valid even if we don't grok it.  However, if we are 
             * authoritative, we can warn the user they did something wrong.
             * That something could be a missing "AuthAuthoritative off", but
             * more likely is a typo in the require directive.
             */
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "access to %s failed, reason: unknown require "
                          "directive:\"%s\"", r->uri, reqs[x].requirement);
        }
    }

    if (!method_restricted) {
