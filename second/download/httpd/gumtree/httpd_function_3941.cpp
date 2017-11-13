static const char *util_ldap_set_chase_referrals(cmd_parms *cmd,
                                                 void *config,
                                                 int mode)
{
    util_ldap_config_t *dc =  config;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                      "LDAP: Setting referral chasing %s",
                      (mode == AP_LDAP_CHASEREFERRALS_ON) ? "ON" : "OFF");

    dc->ChaseReferrals = mode;

    return(NULL);
}