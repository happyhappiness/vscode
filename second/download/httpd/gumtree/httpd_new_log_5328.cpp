ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(),
                             ap_server_conf, APLOGNO(00342)
                             "setsockopt(SO_UPDATE_ACCEPT_CONTEXT) failed.");