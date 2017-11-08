static int authorize_user(request_rec *r)
{
    authz_core_dir_conf *conf;
    authz_status auth_result;

    conf = ap_get_module_config(r->per_dir_config, &authz_core_module);

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
    else if (auth_result == AUTHZ_DENIED || auth_result == AUTHZ_NEUTRAL) {
        if (r->ap_auth_type == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r,
                          "client denied by server configuration: %s%s",
                          r->filename ? "" : "uri ",
                          r->filename ? r->filename : r->uri);

            return HTTP_FORBIDDEN;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r,
                          "user %s: authorization failure for \"%s\": ",
                          r->user, r->uri);

            /* If we're returning 403, tell them to try again. */
            ap_note_auth_failure(r);

            return HTTP_UNAUTHORIZED;
        }
    }
    else {
        /* We'll assume that the module has already said what its
         * error was in the logs.
         */
        return HTTP_INTERNAL_SERVER_ERROR;
    }
}