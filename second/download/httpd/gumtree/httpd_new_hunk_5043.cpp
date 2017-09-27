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
