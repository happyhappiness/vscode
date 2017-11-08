static authn_status check_anonymous(request_rec *r, const char *user,
                                    const char *sent_pw)
{
    authn_anon_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                      &authn_anon_module);
    authn_status res = AUTH_USER_NOT_FOUND;

    /* Ignore if we are not configured */
    if (!conf->users && !conf->anyuserid) {
        return AUTH_USER_NOT_FOUND;
    }

    /* Do we allow an empty userID and/or is it the magic one
     */
    if (!*user) {
        if (conf->nouserid) {
            res = AUTH_USER_FOUND;
        }
    }
    else if (conf->anyuserid) {
        res = AUTH_USER_FOUND;
    }
    else {
        anon_auth_user *p = conf->users;

        while (p) {
            if (!strcasecmp(user, p->user)) {
                res = AUTH_USER_FOUND;
                break;
            }
            p = p->next;
        }
    }

    /* Now if the supplied user-ID was ok, grant access if:
     * (a) no passwd was sent and no password and no verification
     *     were configured.
     * (b) password was sent and no verification was configured
     * (c) verification was configured and the password (sent or not)
     *     looks like an email address
     */
    if (   (res == AUTH_USER_FOUND)
        && (!conf->mustemail || *sent_pw)
        && (   !conf->verifyemail
            || (ap_strchr_c(sent_pw, '@') && ap_strchr_c(sent_pw, '.'))))
    {
        if (conf->logemail && ap_is_initial_req(r)) {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, APR_SUCCESS, r,
                          "Anonymous: Passwd <%s> Accepted",
                          sent_pw ? sent_pw : "\'none\'");
        }

        return AUTH_GRANTED;
    }

    return (res == AUTH_USER_NOT_FOUND ? res : AUTH_DENIED);
}