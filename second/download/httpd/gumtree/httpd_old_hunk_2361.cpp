     */
    if ((access_status = ap_run_type_checker(r)) != OK) {
        return decl_die(access_status, "find types", r);
    }

    if ((access_status = ap_run_fixups(r)) != OK) {
        return access_status;
    }

    return OK;
}

