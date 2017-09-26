                if (pkey_mtime) {
                    int i;

                    for (i=0; i < SSL_AIDX_MAX; i++) {
                        const char *key_id =
                            ssl_asn1_table_keyfmt(p, cpVHostID, i);
                        ssl_asn1_t *asn1 = 
                            ssl_asn1_table_get(mc->tPrivateKey, key_id);
                    
                        if (asn1 && (asn1->source_mtime == pkey_mtime)) {
                            ap_log_error(APLOG_MARK, APLOG_INFO,
                                         0, pServ,
                                         "%s reusing existing "
                                         "%s private key on restart",
                                         cpVHostID, ssl_asn1_keystr(i));
