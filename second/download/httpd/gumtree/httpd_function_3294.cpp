static authz_status host_check_authorization(request_rec *r, const char *require_line)
{
    const char *t, *w;
    const char *remotehost = NULL;
    int remotehost_is_ip;

    remotehost = ap_get_remote_host(r->connection,
                                    r->per_dir_config,
                                    REMOTE_DOUBLE_REV,
                                    &remotehost_is_ip);

    if ((remotehost == NULL) || remotehost_is_ip) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "access to %s failed, reason: unable to get the "
                      "remote host name", r->uri);
    }
    else {
        /* The 'host' provider will allow the configuration to specify a list of
            host names to check rather than a single name.  This is different
            from the previous host based syntax. */
        t = require_line;
        while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
            if (in_domain(w, remotehost)) {
                return AUTHZ_GRANTED;
            }
        }

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "access to %s failed, reason: host name list does not meet "
                      "'require'ments for user '%s' to be allowed access",
                      r->uri, r->user);
    }

    return AUTHZ_DENIED;
}