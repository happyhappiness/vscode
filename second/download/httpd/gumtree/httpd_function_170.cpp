static const char *mod_auth_ldap_parse_url(cmd_parms *cmd, 
                                    void *config,
                                    const char *url)
{
    int result;
    apr_ldap_url_desc_t *urld;

    mod_auth_ldap_config_t *sec = config;

    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0,
	         cmd->server, "[%d] auth_ldap url parse: `%s'", 
	         getpid(), url);

    result = apr_ldap_url_parse(url, &(urld));
    if (result != LDAP_SUCCESS) {
        switch (result) {
        case LDAP_URL_ERR_NOTLDAP:
            return "LDAP URL does not begin with ldap://";
        case LDAP_URL_ERR_NODN:
            return "LDAP URL does not have a DN";
        case LDAP_URL_ERR_BADSCOPE:
            return "LDAP URL has an invalid scope";
        case LDAP_URL_ERR_MEM:
            return "Out of memory parsing LDAP URL";
        default:
            return "Could not parse LDAP URL";
        }
    }
    sec->url = apr_pstrdup(cmd->pool, url);

    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0,
	         cmd->server, "[%d] auth_ldap url parse: Host: %s", getpid(), urld->lud_host);
    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0,
	         cmd->server, "[%d] auth_ldap url parse: Port: %d", getpid(), urld->lud_port);
    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0,
	         cmd->server, "[%d] auth_ldap url parse: DN: %s", getpid(), urld->lud_dn);
    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0,
	         cmd->server, "[%d] auth_ldap url parse: attrib: %s", getpid(), urld->lud_attrs? urld->lud_attrs[0] : "(null)");
    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0,
	         cmd->server, "[%d] auth_ldap url parse: scope: %s", getpid(), 
	         (urld->lud_scope == LDAP_SCOPE_SUBTREE? "subtree" : 
		 urld->lud_scope == LDAP_SCOPE_BASE? "base" : 
		 urld->lud_scope == LDAP_SCOPE_ONELEVEL? "onelevel" : "unknown"));
    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0,
	         cmd->server, "[%d] auth_ldap url parse: filter: %s", getpid(), urld->lud_filter);

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
    if (strncmp(url, "ldaps", 5) == 0) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0,
		     cmd->server, "[%d] auth_ldap parse url: requesting secure LDAP", getpid());
#ifdef APU_HAS_LDAP_STARTTLS
        sec->port = urld->lud_port? urld->lud_port : LDAPS_PORT;
        sec->starttls = 1;
#else
#ifdef APU_HAS_LDAP_NETSCAPE_SSL
        sec->port = urld->lud_port? urld->lud_port : LDAPS_PORT;
        sec->netscapessl = 1;
#else
        return "Secure LDAP (ldaps://) not supported. Rebuild APR-Util";
#endif
#endif
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0,
		     cmd->server, "[%d] auth_ldap parse url: not requesting secure LDAP", getpid());
        sec->netscapessl = 0;
        sec->starttls = 0;
        sec->port = urld->lud_port? urld->lud_port : LDAP_PORT;
    }

    sec->have_ldap_url = 1;
    apr_ldap_free_urldesc(urld);
    return NULL;
}