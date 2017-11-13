ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02031)
                        "Hostname %s provided via SNI, but no hostname"
                        " provided in HTTP request", servername);