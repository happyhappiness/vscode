    const char *orig_groups = NULL;
    const char *realm = ap_auth_name(r);
    const char *groups;
    char *v;

    if (!user) {
        return AUTHZ_DENIED_NO_USER;
    }

    if (!conf->grpfile) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "No group file was specified in the configuration");
        return AUTHZ_DENIED;
