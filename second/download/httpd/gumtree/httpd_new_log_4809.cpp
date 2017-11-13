ap_log_error(APLOG_MARK, APLOG_INFO,
                                     0, pServ, APLOGNO(02244)
                                     "%s reusing existing "
                                     "%s private key on restart",
                                     cpVHostID, ssl_asn1_keystr(i));