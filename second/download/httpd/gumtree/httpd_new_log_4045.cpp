ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01312)
                 "LDAP: Limit chased referrals to maximum of %d hops.",
                 dc->ReferralHopLimit);