static int check_authn(request_rec * r, const char *sent_user, const char *sent_pw)
{
    authn_status auth_result;
    authn_provider_list *current_provider;
    auth_form_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                      &auth_form_module);

    current_provider = conf->providers;
    do {
        const authn_provider *provider;

        /*
         * For now, if a provider isn't set, we'll be nice and use the file
         * provider.
         */
        if (!current_provider) {
            provider = ap_lookup_provider(AUTHN_PROVIDER_GROUP,
                                          AUTHN_DEFAULT_PROVIDER,
                                          AUTHN_PROVIDER_VERSION);

            if (!provider || !provider->check_password) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
                              "no authn provider configured");
                auth_result = AUTH_GENERAL_ERROR;
                break;
            }
            apr_table_setn(r->notes, AUTHN_PROVIDER_NAME_NOTE, AUTHN_DEFAULT_PROVIDER);
        }
        else {
            provider = current_provider->provider;
            apr_table_setn(r->notes, AUTHN_PROVIDER_NAME_NOTE, current_provider->provider_name);
        }

        if (!sent_user || !sent_pw) {
            auth_result = AUTH_USER_NOT_FOUND;
            break;
        }

        auth_result = provider->check_password(r, sent_user, sent_pw);

        apr_table_unset(r->notes, AUTHN_PROVIDER_NAME_NOTE);

        /* Something occured. Stop checking. */
        if (auth_result != AUTH_USER_NOT_FOUND) {
            break;
        }

        /* If we're not really configured for providers, stop now. */
        if (!conf->providers) {
            break;
        }

        current_provider = current_provider->next;
    } while (current_provider);

    if (auth_result != AUTH_GRANTED) {
        int return_code;

        /* If we're not authoritative, then any error is ignored. */
        if (!(conf->authoritative) && auth_result != AUTH_DENIED) {
            return DECLINED;
        }

        switch (auth_result) {
        case AUTH_DENIED:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
                          "user '%s': authentication failure for \"%s\": "
                          "password Mismatch",
                          sent_user, r->uri);
            return_code = HTTP_UNAUTHORIZED;
            break;
        case AUTH_USER_NOT_FOUND:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
                          "user '%s' not found: %s", sent_user, r->uri);
            return_code = HTTP_UNAUTHORIZED;
            break;
        case AUTH_GENERAL_ERROR:
        default:
            /*
             * We'll assume that the module has already said what its error
             * was in the logs.
             */
            return_code = HTTP_INTERNAL_SERVER_ERROR;
            break;
        }

        /* If we're returning 403, tell them to try again. */
        if (return_code == HTTP_UNAUTHORIZED) {
            note_cookie_auth_failure(r);
        }

/* TODO: Flag the user somehow as to the reason for the failure */

        return return_code;
    }

    return OK;

}