    if (!conf->section) {
        if (ap_auth_type(r)) {
            /* there's an AuthType configured, but no authorization
             * directives applied to support it
             */

            ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r,
                          "AuthType configured with no corresponding "
                          "authorization directives");

            return HTTP_INTERNAL_SERVER_ERROR;
        }

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r,
                      "authorization result: granted (no directives)");

        return OK;
    }

    auth_result = apply_authz_sections(r, conf->section, AUTHZ_LOGIC_AND);

    if (auth_result == AUTHZ_GRANTED) {
        return OK;
    }
    else if (auth_result == AUTHZ_DENIED_NO_USER) {
        if (after_authn) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r,
                          "authorization failure (no authenticated user): %s",
                          r->uri);
            /*
             * If we're returning 401 to an authenticated user, tell them to
             * try again. If unauthenticated, note_auth_failure has already
             * been called during auth.
