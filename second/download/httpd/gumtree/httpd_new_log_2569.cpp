ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "Making local copy of SGL for "
                                  "group (%s)(objectClass=%s) ",
                                  dn, (char *)sgc_ents[base_sgcIndex].name);