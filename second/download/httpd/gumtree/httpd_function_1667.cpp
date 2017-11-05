static const char *util_ldap_set_referral_hop_limit(cmd_parms *cmd,
                                                    void *config,
                                                    const char *hop_limit)
{
    util_ldap_config_t *dc =  config;

    dc->ReferralHopLimit = atol(hop_limit);

    if (dc->ReferralHopLimit <= 0) { 
        return "LDAPReferralHopLimit must be greater than zero (Use 'LDAPReferrals Off' to disable referral chasing)";
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "LDAP: Limit chased referrals to maximum of %d hops.",
                 dc->ReferralHopLimit);

    return NULL;
}