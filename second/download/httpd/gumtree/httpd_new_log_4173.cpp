ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01909)
                         "%s certificate configured for %s does NOT include "
                         "an ID which matches the server name",
                         ssl_asn1_keystr(type), (mySrvConfig(s))->vhost_id);