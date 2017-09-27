        }
        else {
            provider = current_provider->provider;
            apr_table_setn(r->notes, AUTHN_PROVIDER_NAME_NOTE, current_provider->provider_name);
        }


        auth_result = provider->check_password(r, sent_user, sent_pw);

        apr_table_unset(r->notes, AUTHN_PROVIDER_NAME_NOTE);

        /* Something occured. Stop checking. */
        if (auth_result != AUTH_USER_NOT_FOUND) {
            break;
