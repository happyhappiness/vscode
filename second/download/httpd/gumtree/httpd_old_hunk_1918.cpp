    /* Rerun the location walk, which overrides any map_to_storage config.
     */
    if ((access_status = ap_location_walk(r))) {
        return access_status;
    }

    /* Only on the main request! */
    if (r->main == NULL) {
        if ((access_status = ap_run_header_parser(r))) {
            return access_status;
        }
    }

    /* Skip authn/authz if the parent or prior request passed the authn/authz,
     * and that configuration didn't change (this requires optimized _walk()
     * functions in map_to_storage that use the same merge results given
     * identical input.)  If the config changes, we must re-auth.
     */
    if (r->main && (r->main->per_dir_config == r->per_dir_config)) {
        r->user = r->main->user;
        r->ap_auth_type = r->main->ap_auth_type;
    }
    else if (r->prev && (r->prev->per_dir_config == r->per_dir_config)) {
        r->user = r->prev->user;
        r->ap_auth_type = r->prev->ap_auth_type;
    }
    else {
        /* A module using a confusing API (ap_get_basic_auth_pw) caused
        ** r->user to be filled out prior to check_authn hook. We treat
        ** it is inadvertent.
        */
        if (r->user && apr_table_get(r->notes, AP_GET_BASIC_AUTH_PW_NOTE)) { 
            r->user = NULL;
        }

        switch (ap_satisfies(r)) {
        case SATISFY_ALL:
        case SATISFY_NOSPEC:
            if ((access_status = ap_run_access_checker(r)) != 0) {
                return decl_die(access_status, "check access", r);
            }

            if (ap_some_auth_required(r)) {
                if (((access_status = ap_run_check_user_id(r)) != 0)
                    || !ap_auth_type(r)) {
                    return decl_die(access_status, ap_auth_type(r)
                                  ? "check user.  Check your authn provider!"
                                  : "perform authentication. AuthType not set!",
                                  r);
                }

                if (((access_status = ap_run_auth_checker(r)) != 0)
                    || !ap_auth_type(r)) {
                    return decl_die(access_status, ap_auth_type(r)
                                  ? "check access.  Check your 'Require' directive"
                                  : "perform authentication. AuthType not set!",
                                   r);
                }
            }
            break;

        case SATISFY_ANY:
            if (((access_status = ap_run_access_checker(r)) != 0)) {
                if (!ap_some_auth_required(r)) {
                    return decl_die(access_status, "check access", r);
                }

                if (((access_status = ap_run_check_user_id(r)) != 0)
                    || !ap_auth_type(r)) {
                    return decl_die(access_status, ap_auth_type(r)
                                  ? "check user.  Check your authn provider!"
                                  : "perform authentication. AuthType not set!",
                                  r);
                }

                if (((access_status = ap_run_auth_checker(r)) != 0)
                    || !ap_auth_type(r)) {
                    return decl_die(access_status, ap_auth_type(r)
                                  ? "check access.  Check your 'Require' directive"
                                  : "perform authentication. AuthType not set!",
                                  r);
                }
            }
            break;
        }
    }
    /* XXX Must make certain the ap_run_type_checker short circuits mime
     * in mod-proxy for r->proxyreq && r->parsed_uri.scheme
     *                              && !strcmp(r->parsed_uri.scheme, "http")
     */
    if ((access_status = ap_run_type_checker(r)) != 0) {
        return decl_die(access_status, "find types", r);
    }

    if ((access_status = ap_run_fixups(r)) != 0) {
        return access_status;
    }

    return OK;
}

