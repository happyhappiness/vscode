ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s,
                     "Failed to read %d bytes from %s: (%d) %pm",
                     TLSEXT_TICKET_KEY_LEN, path, rv, &rv);