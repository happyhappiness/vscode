static int authenticate_no_user(request_rec *r)
{
    authn_default_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                      &authn_default_module);

    const char *type;

    if (!(type = ap_auth_type(r))) {
        return DECLINED;
    }

    /* fill in the r->user field */
    if (!strcasecmp(type, "Basic")) {
        const char *sent_pw;
        int res;

        if ((res = ap_get_basic_auth_pw(r, &sent_pw)) != OK) {
            return res;
        }
    }

    if (conf->authoritative == 0) {
        return DECLINED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "access to %s failed, reason: verification of user id '%s' "
                  "not configured",
                  r->uri, r->user ? r->user : "<null>");

    ap_note_auth_failure(r);
    return HTTP_UNAUTHORIZED;
}