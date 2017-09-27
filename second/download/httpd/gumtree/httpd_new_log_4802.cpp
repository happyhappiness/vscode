ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01910)
                "Oops, no " KEYTYPES " server certificate found "
                "for '%s:%d'?!", s->server_hostname, s->port);