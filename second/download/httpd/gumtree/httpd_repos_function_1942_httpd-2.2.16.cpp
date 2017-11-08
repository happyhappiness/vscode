static const char *mod_auth_ldap_parse_url(cmd_parms *cmd,
                                    void *config,
                                    const char *url,
                                    const char *mode)
{
    int rc;
    apr_ldap_url_desc_t *urld;
    apr_ldap_err_t *result;

    authn_ldap_config_t *sec = config;

    rc = apr_ldap_url_parse(cmd->pool, url, &(urld), &(result));
    if (rc != APR_SUCCESS) {
        return result->reason;
    }
    sec->url = apr_pstrdup(cmd->pool, url);

    /* Set all the values, or at least some sane defaults */
    if (sec->host) {
        char *p = apr_palloc(cmd->pool, strlen(sec->host) + strlen(urld->lud_host) + 2);
        strcpy(p, urld->lud_host);
        strcat(p, " ");
        strcat(p, sec->host);
        sec->host = p;
    }
    else {
        sec->host = urld->lud_host? apr_pstrdup(cmd->pool, urld->lud_host) : "localhost";
    }
    sec->basedn = urld->lud_dn? apr_pstrdup(cmd->pool, urld->lud_dn) : "";
    if (urld->lud_attrs && urld->lud_attrs[0]) {
        int i = 1;
        while (urld->lud_attrs[i]) {
            i++;
        }
        sec->attributes = apr_pcalloc(cmd->pool, sizeof(char *) * (i+1));
        i = 0;
        while (urld->lud_attrs[i]) {
            sec->attributes[i] = apr_pstrdup(cmd->pool, urld->lud_attrs[i]);
            i++;
        }
        sec->attribute = sec->attributes[0];
    }
    else {
        sec->attribute = "uid";
    }

    sec->scope = urld->lud_scope == LDAP_SCOPE_ONELEVEL ?
        LDAP_SCOPE_ONELEVEL : LDAP_SCOPE_SUBTREE;

    if (urld->lud_filter) {
        if (urld->lud_filter[0] == '(') {
            /*
             * Get rid of the surrounding parens; later on when generating the
             * filter, they'll be put back.
             */
            sec->filter = apr_pstrdup(cmd->pool, urld->lud_filter+1);
            sec->filter[strlen(sec->filter)-1] = '\0';
        }
        else {
            sec->filter = apr_pstrdup(cmd->pool, urld->lud_filter);
        }
    }
    else {
        sec->filter = "objectclass=*";
    }

    if (mode) {
        if (0 == strcasecmp("NONE", mode)) {
            sec->secure = APR_LDAP_NONE;
        }
        else if (0 == strcasecmp("SSL", mode)) {
            sec->secure = APR_LDAP_SSL;
        }
        else if (0 == strcasecmp("TLS", mode) || 0 == strcasecmp("STARTTLS", mode)) {
            sec->secure = APR_LDAP_STARTTLS;
        }
        else {
            return "Invalid LDAP connection mode setting: must be one of NONE, "
                   "SSL, or TLS/STARTTLS";
        }
    }

      /* "ldaps" indicates secure ldap connections desired
      */
    if (strncasecmp(url, "ldaps", 5) == 0)
    {
        sec->secure = APR_LDAP_SSL;
        sec->port = urld->lud_port? urld->lud_port : LDAPS_PORT;
    }
    else
    {
        sec->port = urld->lud_port? urld->lud_port : LDAP_PORT;
    }

    sec->have_ldap_url = 1;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                 cmd->server, "[%" APR_PID_T_FMT "] auth_ldap url parse: `%s', Host: %s, Port: %d, DN: %s, attrib: %s, scope: %s, filter: %s, connection mode: %s",
                 getpid(),
                 url,
                 urld->lud_host,
                 urld->lud_port,
                 urld->lud_dn,
                 urld->lud_attrs? urld->lud_attrs[0] : "(null)",
                 (urld->lud_scope == LDAP_SCOPE_SUBTREE? "subtree" :
                  urld->lud_scope == LDAP_SCOPE_BASE? "base" :
                  urld->lud_scope == LDAP_SCOPE_ONELEVEL? "onelevel" : "unknown"),
                 urld->lud_filter,
                 sec->secure == APR_LDAP_SSL  ? "using SSL": "not using SSL"
                 );

    return NULL;
}