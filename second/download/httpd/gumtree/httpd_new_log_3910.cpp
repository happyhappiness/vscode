ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01281)
                        "Unable to set LDAP_OPT_REFHOPLIMIT option to %d: %d.",
                        ldc->ReferralHopLimit,
                        result->rc);