
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

static int authz_some_auth_required(request_rec *r)
{
    authz_core_dir_conf *conf;

    conf = ap_get_module_config(r->per_dir_config, &authz_core_module);

