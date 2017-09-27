    int rc;
    apr_ldap_url_desc_t *urld;
    apr_ldap_err_t *result;

    authn_ldap_config_t *sec = config;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                 cmd->server, "[%" APR_PID_T_FMT "] auth_ldap url parse: `%s'", getpid(), url);

    rc = apr_ldap_url_parse(cmd->pool, url, &(urld), &(result));
    if (rc != APR_SUCCESS) {
        return result->reason;
    }
    sec->url = apr_pstrdup(cmd->pool, url);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                 cmd->server, "[%" APR_PID_T_FMT "] auth_ldap url parse: Host: %s", getpid(), urld->lud_host);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                 cmd->server, "[%" APR_PID_T_FMT "] auth_ldap url parse: Port: %d", getpid(), urld->lud_port);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                 cmd->server, "[%" APR_PID_T_FMT "] auth_ldap url parse: DN: %s", getpid(), urld->lud_dn);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                 cmd->server, "[%" APR_PID_T_FMT "] auth_ldap url parse: attrib: %s", getpid(), urld->lud_attrs? urld->lud_attrs[0] : "(null)");
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                 cmd->server, "[%" APR_PID_T_FMT "] auth_ldap url parse: scope: %s", getpid(),
                 (urld->lud_scope == LDAP_SCOPE_SUBTREE? "subtree" :
                  urld->lud_scope == LDAP_SCOPE_BASE? "base" :
                  urld->lud_scope == LDAP_SCOPE_ONELEVEL? "onelevel" : "unknown"));
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                 cmd->server, "[%" APR_PID_T_FMT "] auth_ldap url parse: filter: %s", getpid(), urld->lud_filter);

    /* Set all the values, or at least some sane defaults */
    if (sec->host) {
        char *p = apr_palloc(cmd->pool, strlen(sec->host) + strlen(urld->lud_host) + 2);
        strcpy(p, urld->lud_host);
        strcat(p, " ");
        strcat(p, sec->host);
