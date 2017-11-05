static int authenticate_basic_user(request_rec *r)
{
    auth_basic_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                       &auth_basic_module);
    const char *sent_user, *sent_pw, *current_auth;
    const char *realm = NULL;
    const char *digest = NULL;
    int res;
    authn_status auth_result;
    authn_provider_list *current_provider;

    /* Are we configured to be Basic auth? */
    current_auth = ap_auth_type(r);
    if (!current_auth || strcasecmp(current_auth, "Basic")) {
        return DECLINED;
    }

    /* We need an authentication realm. */
    if (!ap_auth_name(r)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR,
                      0, r, APLOGNO(01615) "need AuthName: %s", r->uri);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    r->ap_auth_type = (char*)current_auth;

    res = get_basic_auth(r, &sent_user, &sent_pw);
    if (res) {
        return res;
    }

    if (conf->use_digest_algorithm
        && !strcasecmp(conf->use_digest_algorithm, "MD5")) {
        realm = ap_auth_name(r);
        digest = ap_md5(r->pool,
                        (unsigned char *)apr_pstrcat(r->pool, sent_user, ":",
                                                     realm, ":",
                                                     sent_pw, NULL));
    }

    current_provider = conf->providers;
    do {
        const authn_provider *provider;

        /* For now, if a provider isn't set, we'll be nice and use the file
         * provider.
         */
        if (!current_provider) {
            provider = ap_lookup_provider(AUTHN_PROVIDER_GROUP,
                                          AUTHN_DEFAULT_PROVIDER,
                                          AUTHN_PROVIDER_VERSION);

            if (!provider || !provider->check_password) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01616)
                              "No Authn provider configured");
                auth_result = AUTH_GENERAL_ERROR;
                break;
            }
            apr_table_setn(r->notes, AUTHN_PROVIDER_NAME_NOTE, AUTHN_DEFAULT_PROVIDER);
        }
        else {
            provider = current_provider->provider;
            apr_table_setn(r->notes, AUTHN_PROVIDER_NAME_NOTE, current_provider->provider_name);
        }

        if (digest) {
            char *password;

            if (!provider->get_realm_hash) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02493)
                              "Authn provider does not support "
                              "AuthBasicUseDigestAlgorithm");
                auth_result = AUTH_GENERAL_ERROR;
                break;
            }
            /* We expect the password to be hash of user:realm:password */
            auth_result = provider->get_realm_hash(r, sent_user, realm,
                                                   &password);
            if (auth_result == AUTH_USER_FOUND) {
                auth_result = strcmp(digest, password) ? AUTH_DENIED
                                                       : AUTH_GRANTED;
            }
        }
        else {
            auth_result = provider->check_password(r, sent_user, sent_pw);
        }

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
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01617)
                      "user %s: authentication failure for \"%s\": "
                      "Password Mismatch",
                      sent_user, r->uri);
            return_code = HTTP_UNAUTHORIZED;
            break;
        case AUTH_USER_NOT_FOUND:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01618)
                      "user %s not found: %s", sent_user, r->uri);
            return_code = HTTP_UNAUTHORIZED;
            break;
        case AUTH_GENERAL_ERROR:
        default:
            /* We'll assume that the module has already said what its error
             * was in the logs.
             */
            return_code = HTTP_INTERNAL_SERVER_ERROR;
            break;
        }

        /* If we're returning 403, tell them to try again. */
        if (return_code == HTTP_UNAUTHORIZED) {
            note_basic_auth_failure(r);
        }
        return return_code;
    }

    return OK;
}