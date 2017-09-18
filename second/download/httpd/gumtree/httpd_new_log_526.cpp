ap_log_error(APLOG_MARK, APLOG_INFO,
                                         0, pServ,
                                         "%s reusing existing "
                                         "%s private key on restart",
                                         cpVHostID, ssl_asn1_keystr(i));