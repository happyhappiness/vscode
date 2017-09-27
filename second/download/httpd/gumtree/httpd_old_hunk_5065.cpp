    return NULL;
}


static const char *util_ldap_set_chase_referrals(cmd_parms *cmd,
                                                 void *config,
                                                 int mode)
{
    util_ldap_config_t *dc =  config;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01311)
                      "LDAP: Setting referral chasing %s",
                      (mode == AP_LDAP_CHASEREFERRALS_ON) ? "ON" : "OFF");

    dc->ChaseReferrals = mode;

    return(NULL);
}

static const char *util_ldap_set_debug_level(cmd_parms *cmd,
                                             void *config,
