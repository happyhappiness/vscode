ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01908)
                             "%sID '%s' in %s certificate configured "
                             "for %s matches server name",
                             is_wildcard ? "Wildcard " : "",
                             id[i], ssl_asn1_keystr(type),
                             (mySrvConfig(s))->vhost_id);