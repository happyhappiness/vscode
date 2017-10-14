static authz_status ip_check_authorization(request_rec *r, const char *require_line)
{
    const char *t, *w;

    /* The 'ip' provider will allow the configuration to specify a list of
        ip addresses to check rather than a single address.  This is different
        from the previous host based syntax. */
    t = require_line;
    while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
        char *where = apr_pstrdup(r->pool, w);
        char *s;
        char msgbuf[120];
        apr_ipsubnet_t *ip;
        apr_status_t rv;
        int got_ip = 0;

        if ((s = ap_strchr(where, '/'))) {
            *s++ = '\0';
            rv = apr_ipsubnet_create(&ip, where, s, r->pool);
            if(APR_STATUS_IS_EINVAL(rv)) {
                /* looked nothing like an IP address */
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "an ip address 'require' list appears to be invalid ");
            }
            else if (rv != APR_SUCCESS) {
                apr_strerror(rv, msgbuf, sizeof msgbuf);
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "an ip address 'require' list appears to be invalid; %s ",
                              msgbuf);
            }
            else
                got_ip = 1;
        }
        else if (!APR_STATUS_IS_EINVAL(rv = apr_ipsubnet_create(&ip, where,
                                                                NULL, r->pool))) {
            if (rv != APR_SUCCESS) {
                apr_strerror(rv, msgbuf, sizeof msgbuf);
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "an ip address 'require' list appears to be invalid; %s ",
                              msgbuf);
            }
            else 
                got_ip = 1;
        }

        if (got_ip && apr_ipsubnet_test(ip, r->connection->remote_addr)) {
            return AUTHZ_GRANTED;
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "access to %s failed, reason: ip address list does not meet "
                  "'require'ments for user '%s' to be allowed access",
                  r->uri, r->user);

    return AUTHZ_DENIED;
}