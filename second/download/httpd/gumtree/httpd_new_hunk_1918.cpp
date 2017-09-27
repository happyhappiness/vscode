    /* Rerun the location walk, which overrides any map_to_storage config.
     */
    if ((access_status = ap_location_walk(r))) {
        return access_status;
    }

    d = ap_get_module_config(r->per_dir_config, &core_module);
    if (d->log) {
        r->log = d->log;
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
    if (r->prev && (r->prev->per_dir_config == r->per_dir_config)) {
        r->user = r->prev->user;
        r->ap_auth_type = r->prev->ap_auth_type;
    }
    else if (r->main && (r->main->per_dir_config == r->per_dir_config)) {
        r->user = r->main->user;
        r->ap_auth_type = r->main->ap_auth_type;
    }
    else {
        switch (ap_satisfies(r)) {
        case SATISFY_ALL:
        case SATISFY_NOSPEC:
            if ((access_status = ap_run_access_checker(r)) != OK) {
                return decl_die(access_status, "check access", r);
            }

            if ((access_status = ap_run_check_user_id(r)) != OK) {
                return decl_die(access_status, "check user", r);
            }

            if ((access_status = ap_run_auth_checker(r)) != OK) {
                return decl_die(access_status, "check authorization", r);
            }
            break;
        case SATISFY_ANY:
            if ((access_status = ap_run_access_checker(r)) != OK) {

                if ((access_status = ap_run_check_user_id(r)) != OK) {
                    return decl_die(access_status, "check user", r);
                }

                if ((access_status = ap_run_auth_checker(r)) != OK) {
                    return decl_die(access_status, "check authorization", r);
                }
            }
            break;
        }


    }
    /* XXX Must make certain the ap_run_type_checker short circuits mime
     * in mod-proxy for r->proxyreq && r->parsed_uri.scheme
     *                              && !strcmp(r->parsed_uri.scheme, "http")
     */
    if ((access_status = ap_run_type_checker(r)) != OK) {
        return decl_die(access_status, "find types", r);
    }

    if ((access_status = ap_run_fixups(r)) != OK) {
        return access_status;
    }

    return OK;
}

