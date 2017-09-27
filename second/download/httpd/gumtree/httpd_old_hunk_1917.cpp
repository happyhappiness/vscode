     */
    if (!file_req) {
        if ((access_status = ap_location_walk(r))) {
            return access_status;
        }

        if ((access_status = ap_run_translate_name(r))) {
            return decl_die(access_status, "translate", r);
        }
    }

    /* Reset to the server default config prior to running map_to_storage
