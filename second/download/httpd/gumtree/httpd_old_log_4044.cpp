ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                      "LDAP: Setting referral chasing %s",
                      (mode == AP_LDAP_CHASEREFERRALS_ON) ? "ON" : "OFF");