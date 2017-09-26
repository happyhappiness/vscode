      /* "ldaps" indicates secure ldap connections desired
      */
    if (strncasecmp(url, "ldaps", 5) == 0)
    {
        sec->secure = APR_LDAP_SSL;
        sec->port = urld->lud_port? urld->lud_port : LDAPS_PORT;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                     "LDAP: auth_ldap using SSL connections");
    }
    else
    {
        sec->port = urld->lud_port? urld->lud_port : LDAP_PORT;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                     "LDAP: auth_ldap not using SSL connections");
    }

    sec->have_ldap_url = 1;

    return NULL;
}

static const char *mod_auth_ldap_set_deref(cmd_parms *cmd, void *config, const char *arg)
{
    authn_ldap_config_t *sec = config;
