static authz_status apply_authz_sections(request_rec *r,
                                         authz_section_conf *section,
                                         authz_logic_op parent_op)
{
    authz_status auth_result;

    /* check to make sure that the request method requires authorization */
    if (!(section->limited & (AP_METHOD_BIT << r->method_number))) {
        auth_result =
            (parent_op == AUTHZ_LOGIC_AND) ? AUTHZ_GRANTED : AUTHZ_NEUTRAL;

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r,
                      "authorization result of %s: %s "
                      "(directive limited to other methods)",
                      format_authz_command(r->pool, section),
                      format_authz_result(auth_result));

        return auth_result;
    }

    if (section->provider) {
        apr_table_setn(r->notes, AUTHZ_PROVIDER_NAME_NOTE,
                       section->provider_name);

        auth_result =
            section->provider->check_authorization(r, section->provider_args);

        apr_table_unset(r->notes, AUTHZ_PROVIDER_NAME_NOTE);
    }
    else {
        authz_section_conf *child = section->first;

        auth_result = AUTHZ_NEUTRAL;

        while (child) {
            authz_status child_result;

            child_result = apply_authz_sections(r, child, section->op);

            if (child_result == AUTHZ_GENERAL_ERROR) {
                return AUTHZ_GENERAL_ERROR;
            }

            if (child_result != AUTHZ_NEUTRAL) {
                /*
                 * Handling of AUTHZ_DENIED/AUTHZ_DENIED_NO_USER: Return
                 * AUTHZ_DENIED_NO_USER if providing a user may change the
                 * result, AUTHZ_DENIED otherwise.
                 */
                if (!(section->op == AUTHZ_LOGIC_AND
                      && auth_result == AUTHZ_DENIED
                      && child_result == AUTHZ_DENIED_NO_USER)
                    && !(section->op == AUTHZ_LOGIC_OR
                         && auth_result == AUTHZ_DENIED_NO_USER
                         && child_result == AUTHZ_DENIED) )
                {
                    auth_result = child_result;
                }

                if ((section->op == AUTHZ_LOGIC_AND
                     && child_result == AUTHZ_DENIED)
                    || (section->op == AUTHZ_LOGIC_OR
                        && child_result == AUTHZ_GRANTED)) {
                    break;
                }
            }

            child = child->next;
        }
    }

    if (section->negate) {
        if (auth_result == AUTHZ_GRANTED) {
            auth_result = AUTHZ_DENIED;
        }
        else if (auth_result == AUTHZ_DENIED ||
                 auth_result == AUTHZ_DENIED_NO_USER) {
            /* For negated directives, if the original result was denied
             * then the new result is neutral since we can not grant
             * access simply because authorization was not rejected.
             */
            auth_result = AUTHZ_NEUTRAL;
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r,
                  "authorization result of %s: %s",
                  format_authz_command(r->pool, section),
                  format_authz_result(auth_result));

    return auth_result;
}